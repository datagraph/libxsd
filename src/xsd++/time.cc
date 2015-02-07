/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_TIME_CAPTURES */
#include "regex.h"   /* for std::regex, std::regex_match() */
#include "time.h"

#include "utility/integer.h"

#include <algorithm> /* for std::copy() */
#include <array>     /* for std::array */
#include <cassert>   /* for assert() */
#include <cstdio>    /* for std::snprintf(), std::sprintf() */
#include <cstdlib>   /* for std::abs(), std::atol() */
#include <cstring>   /* for std::strchr() */

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#include <ctime>     /* for struct tm, timegm() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char time::name[];

constexpr char time::pattern[];

static const std::regex time_regex{time::pattern};

static const std::regex timezone_regex{"([-+])([0-9]{2}):([0-9]{2})"};

////////////////////////////////////////////////////////////////////////////////

/**
 * @see http://www.w3.org/TR/xmlschema11-2/#nt-timeRep
 */
static bool
parse_literal(const char* literal,
              xsd::time::model_type& time) {

  std::cmatch matches;
  if (!std::regex_match(literal, matches, time_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  assert(matches.size() == XSD_TIME_CAPTURES);

  /* http://www.w3.org/TR/xmlschema11-2/#nt-hrFrag */
  time.hour = parse_integer<decltype(time.hour)>(matches[1]);
  if (time.hour > 24) {
    return false; /* invalid literal */
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-miFrag */
  time.minute = parse_integer<decltype(time.minute)>(matches[2]);
  if (time.minute > 59) {
    return false; /* invalid literal */
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-seFrag */
  time.second = parse_integer<decltype(time.second)>(matches[3]);
  if (time.second > 59) {
    return false; /* invalid literal */
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-seFrag */
  if (matches[4].length()) {
    time.microsecond = parse_integer<decltype(time.microsecond)>(matches[4], 1);
    while (time.microsecond >= 1000000) {
      time.microsecond /= 10;
    }
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-tzFrag */
  if (!matches[5].length()) {
    time.tz = false;
    time.tz_hour = 0;
    time.tz_minute = 0;
  }
  else {
    time.tz = true;
    const std::string match{matches[5].first, matches[5].second};
    if (match.compare("Z") == 0 || match.compare("-00:00") == 0 || match.compare("+00:00") == 0) {
      time.tz_hour = 0;
      time.tz_minute = 0;
    }
    else {
      std::cmatch matches;
      std::regex_match(match.c_str(), matches, timezone_regex, match_not_null);
      assert(matches.size() == 3);
      const bool sign = !matches[1].length() || !(*matches[1].first == '-');
      time.tz_hour = parse_integer<decltype(time.tz_hour)>(matches[2]);
      time.tz_minute = parse_integer<decltype(time.tz_minute)>(matches[3]);
      if (sign == false) time.tz_hour = -time.tz_hour;
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool
time::validate(const char* literal) noexcept {
  return time::match(literal);
}

bool
time::match(const char* literal) noexcept {
  return std::regex_match(literal, time_regex, match_not_null);
}

bool
time::canonicalize(std::string& literal) {
  model_type time{};

  if (!parse_literal(literal.c_str(), time)) {
    throw std::invalid_argument{literal}; /* invalid literal */
  }

  time.hour = (time.hour - time.tz_hour) % 24;
  time.minute = (time.minute - time.tz_minute) % 60;

  std::array<char, 256> buffer;
  char* output = buffer.data();

  /* http://www.w3.org/TR/xmlschema11-2/#nt-timeRep */
  output += std::sprintf(output, "%02hu:%02hu:%02hu",
    time.hour, time.minute, time.second);

  /* http://www.w3.org/TR/xmlschema11-2/#nt-seFrag */
  if (time.microsecond) {
    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "%u", time.microsecond);
    auto trailing_zero = std::strchr(buffer, '0');
    if (trailing_zero) *trailing_zero = '\0';
    output += std::sprintf(output, ".%06ld", std::atol(buffer));
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-tzFrag */
  if (time.tz) {
    *output++ = 'Z';
  }

  *output++ = '\0';

  if (literal.compare(buffer.data()) != 0) {
    literal.assign(buffer.data());
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

class time
time::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      throw std::overflow_error{literal};
    }
  }

  return value;
}

class time
time::parse(const char* literal,
            std::error_condition& error) noexcept {
  model_type time{};

  if (!parse_literal(literal, time)) {
    error = std::errc::invalid_argument;
    return {};
  }

  time.hour = (time.hour - time.tz_hour) % 24;
  time.minute = (time.minute - time.tz_minute) % 60;

  struct tm tm = {
    .tm_year = 70,
    .tm_mon  = 0,
    .tm_mday = 1,
    .tm_hour = time.hour,
    .tm_min  = time.minute,
    .tm_sec  = time.second,
  };

  const auto epoch_time = timegm(&tm);
  if (epoch_time == static_cast<time_t>(-1)) {
    error = std::errc::invalid_argument;
    return {};
  }

  return epoch_time * 1000000 + time.microsecond;
}

////////////////////////////////////////////////////////////////////////////////

bool
time::normalize() noexcept {
  return false; /* already in normal form */
}

time::operator value_type() const {
  return _value;
}

std::string
time::literal() const {
  return ""; // TODO
}

time::model_type
time::model() const {
  return {}; // TODO
}

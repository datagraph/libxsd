/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DATE_CAPTURES */
#include "date.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include "utility/integer.h"

#include <algorithm> /* for std::copy() */
#include <array>     /* for std::array */
#include <cassert>   /* for assert() */
#include <cstdio>    /* for std::snprintf(), td::sprintf() */
#include <cstdlib>   /* for std::abs() */

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#include <ctime>     /* for struct tm, timegm() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char date::name[];

constexpr char date::pattern[];

static const std::regex date_regex{date::pattern};

static const std::regex timezone_regex{"([-+])([0-9]{2}):([0-9]{2})"};

////////////////////////////////////////////////////////////////////////////////

/**
 * @see http://www.w3.org/TR/xmlschema11-2/#nt-dateRep
 */
static bool
parse_literal(const char* literal,
              xsd::date::model_type& time) {

  std::cmatch matches;
  if (!std::regex_match(literal, matches, date_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  assert(matches.size() == XSD_DATE_CAPTURES);

  /* http://www.w3.org/TR/xmlschema11-2/#nt-yrFrag */
  const bool sign = !matches[1].length() || !(*matches[1].first == '-');

  /* http://www.w3.org/TR/xmlschema11-2/#nt-yrFrag */
  time.year = parse_integer<decltype(time.year)>(matches[2]);
  if (sign == false) time.year = -time.year;

  /* http://www.w3.org/TR/xmlschema11-2/#nt-moFrag */
  time.month = parse_integer<decltype(time.month)>(matches[3]);
  if (time.month > 12) {
    return false; /* invalid literal */
  }

  /* http://www.w3.org/TR/xmlschema11-2/#nt-daFrag */
  time.day = parse_integer<decltype(time.day)>(matches[4]);
  if (time.day > 31) {
    return false; /* invalid literal */
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
date::validate(const char* literal) noexcept {
  return date::match(literal);
}

bool
date::match(const char* literal) noexcept {
  return std::regex_match(literal, date_regex, match_not_null);
}

bool
date::canonicalize(std::string& literal) {
  model_type time{};

  if (!parse_literal(literal.c_str(), time)) {
    throw std::invalid_argument{literal}; /* invalid literal */
  }

  std::array<char, 256> buffer;
  char* output = buffer.data();

  /* http://www.w3.org/TR/xmlschema11-2/#nt-dateRep */
  output += std::sprintf(output, "%04d-%02hu-%02hu",
    time.year, time.month, time.day);

  /* http://www.w3.org/TR/xmlschema11-2/#nt-tzFrag */
  if (time.tz) {
    *output++ = 'Z'; // FIXME
  }

  *output++ = '\0';

  if (literal.compare(buffer.data()) != 0) {
    literal.assign(buffer.data());
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

date
date::parse(const char* literal) {
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

  return {value};
}

date
date::parse(const char* literal,
            std::error_condition& error) noexcept {
  model_type time{};

  if (!parse_literal(literal, time)) {
    error = std::errc::invalid_argument;
    return {};
  }

  struct tm tm = {
    .tm_year = time.year - 1900,
    .tm_mon  = time.month - 1,
    .tm_mday = time.day,
  };

  const auto epoch_time = timegm(&tm);
  if (epoch_time == static_cast<time_t>(-1)) {
    error = std::errc::invalid_argument;
    return {};
  }

  return epoch_time * 1000000;
}

////////////////////////////////////////////////////////////////////////////////

bool
date::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
date::literal() const {
  return ""; // TODO
}

date::model_type
date::model() const {
  return {}; // TODO
}

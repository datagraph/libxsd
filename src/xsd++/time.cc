/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_TIME_CAPTURES */
#include "regex.h"   /* for std::regex, std::regex_match() */
#include "time.h"

#include <algorithm> /* for std::copy(), std::copy_n() */
#include <cassert>   /* for assert() */
#include <cstdio>    /* for std::sprintf() */
#include <cstdlib>   /* for std::atoi() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char time::name[];

constexpr char time::pattern[];

static const std::regex time_regex{time::pattern};

bool
time::match(const std::string& literal) noexcept {
  return std::regex_match(literal, time_regex, match_not_null);
}

bool
time::validate() const noexcept {
  return time::match(_literal);
}

bool
time::canonicalize() noexcept {
  static auto match_to_int = [](const std::csub_match& match) -> unsigned int {
    const auto length = match.length();
    char buffer[length + 1];
    std::copy_n(match.first, length, buffer);
    buffer[length] = '\0';
    return std::atoi(buffer);
  };

  std::cmatch matches;
  if (!std::regex_match(c_str(), matches, time_regex, match_not_null)) {
    throw std::invalid_argument{c_str()}; /* invalid literal */
  }

  assert(matches.size() == XSD_TIME_CAPTURES);

  char buffer[256] = "";
  char* output = buffer;

  /* TZ */
  int tz_hour = 0, tz_min = 0;
  if (matches[5].length()) {
    const std::string match{matches[5].first, matches[5].second};
    const int sign = (match[0] == '-') ? -1 : 1;

    if (match.compare("Z") != 0 || match.compare("-00:00") != 0 || match.compare("+00:00") != 0) {
      tz_hour = sign * std::atoi(match.c_str() + 1);
      tz_min  = sign * std::atoi(match.c_str() + 4);
    }
  }

  /* "hh" */
  {
    const unsigned int hour = match_to_int(matches[1]);
    if (hour >= 24) {
      throw std::invalid_argument{c_str()}; /* invalid literal */
    }
    output += std::sprintf(output, "%02u", (hour - tz_hour) % 24);
  }

  /* "mm" */
  {
    const unsigned int min = match_to_int(matches[2]);
    if (min >= 60) {
      throw std::invalid_argument{c_str()}; /* invalid literal */
    }
    output += std::sprintf(output, ":%02u", (min - tz_min) % 60);
  }

  /* "ss" */
  {
    const unsigned int sec = match_to_int(matches[3]);
    if (sec >= 60) {
      throw std::invalid_argument{c_str()}; /* invalid literal */
    }
    output += std::sprintf(output, ":%02u", sec);
  }

  /* ".sss" */
  if (matches[4].length()) {
    const std::string match{matches[4].first, matches[4].second};
    // TODO: trim off any trailing zeroes.
    const unsigned int msec = std::atoi(match.c_str() + 1);
    output += std::sprintf(output, ".%u", msec);
  }

  /* TZ */
  if (matches[5].length()) {
    *output++ = 'Z';
  }

  *output++ = '\0';

  if (_literal.compare(buffer) != 0) {
    _literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DATE_CAPTURES */
#include "date.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <algorithm> /* for std::copy(), std::copy_n() */
#include <cassert>   /* for assert() */
#include <cstdio>    /* for std::sprintf() */
#include <cstdlib>   /* for std::atoi() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char date::name[];

constexpr char date::pattern[];

static const std::regex date_regex{date::pattern};

bool
date::match(const std::string& literal) noexcept {
  return std::regex_match(literal, date_regex, match_not_null);
}

bool
date::validate() const noexcept {
  return date::match(_literal);
}

bool
date::canonicalize() noexcept {
  static auto match_to_int = [](const std::csub_match& match) -> unsigned int {
    const auto length = match.length();
    char buffer[length + 1];
    std::copy_n(match.first, length, buffer);
    buffer[length] = '\0';
    return std::atoi(buffer);
  };

  std::cmatch matches;
  if (!std::regex_match(c_str(), matches, date_regex, match_not_null)) {
    throw std::invalid_argument{c_str()}; /* invalid literal */
  }

  assert(matches.size() == XSD_DATE_CAPTURES);

  char buffer[256] = "";
  char* output = buffer;

  /* '-'? */
  if (matches[1].length()) {
    const char sign = *matches[1].first;
    if (sign == '-') {
      *output++ = sign;
    }
  }

  /* 'yyyy' */
  {
    const unsigned int year = match_to_int(matches[2]);
    output += std::sprintf(output, "%04u", year);
  }

  /* 'mm' */
  {
    const unsigned int month = match_to_int(matches[3]);
    if (month > 12) {
      throw std::invalid_argument{c_str()}; /* invalid literal */
    }
    output += std::sprintf(output, "-%02u", month);
  }

  /* 'dd' */
  {
    const unsigned int day = match_to_int(matches[4]);
    if (day > 31) {
      throw std::invalid_argument{c_str()}; /* invalid literal */
    }
    output += std::sprintf(output, "-%02u", day);
  }

  /* 'zzzzzz' */
  if (matches[5].length()) {
    const std::string match{matches[5].first, matches[5].second};
    if (match.compare("Z") == 0 || match.compare("-00:00") == 0 || match.compare("+00:00") == 0) {
      *output++ = 'Z';
    }
    else {
      // TODO: normalize the timezone.
      output = std::copy(matches[5].first, matches[5].second, output);
    }
  }

  *output++ = '\0';

  if (_literal.compare(buffer) != 0) {
    _literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

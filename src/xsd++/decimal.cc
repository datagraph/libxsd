/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DECIMAL_CAPTURES */
#include "decimal.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <algorithm> /* for std::copy() */
#include <cassert>   /* for assert() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char decimal::name[];

constexpr char decimal::pattern[];

static const std::regex decimal_regex{decimal::pattern};

bool
decimal::match(const std::string& literal) noexcept {
  return !literal.empty() && std::regex_match(literal, decimal_regex, match_not_null);
}

bool
decimal::validate() const noexcept {
  return decimal::match(_literal);
}

bool
decimal::canonicalize() noexcept {
  std::cmatch matches;
  if (_literal.empty() || !std::regex_match(c_str(), matches, decimal_regex, match_not_null)) {
    throw std::invalid_argument{c_str()}; /* invalid literal */
  }

  assert(matches.size() == XSD_DECIMAL_CAPTURES);

  char buffer[256] = "";
  char* output = buffer;

  /* 3.2.3.2 'The preceding optional "+" sign is prohibited' */
  if (matches[1].length()) {
    const char sign = *matches[1].first;
    if (sign == '-') {
      *output++ = sign;
    }
  }

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  if (matches[2].length()) {
    output = std::copy(matches[2].first, matches[2].second, output);
  }
  else {
    *output++ = '0';
  }

  /* 3.2.3.2 'The decimal point is required' */
  *output++ = '.';

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  if (matches[3].length()) {
    output = std::copy(matches[3].first, matches[3].second, output);
  }
  else {
    *output++ = '0';
  }

  *output++ = '\0';

  if (_literal.compare(buffer) != 0) {
    _literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

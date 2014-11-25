/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DECIMAL_CAPTURES */
#include "decimal.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <algorithm> /* for std::copy() */
#include <cassert>   /* for assert() */
#include <cinttypes> /* for std::strtoimax() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char decimal::name[];

constexpr char decimal::pattern[];

static const std::regex decimal_regex{decimal::pattern};

////////////////////////////////////////////////////////////////////////////////

static bool
parse_literal(const char* literal,
              bool& sign,
              std::string& integer,
              std::string& fraction) {
  std::cmatch matches;
  if (*literal == '\0' || !std::regex_match(literal, matches, decimal_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  assert(matches.size() == XSD_DECIMAL_CAPTURES);

  /* 3.2.3.2 'The preceding optional "+" sign is prohibited' */
  if (matches[1].length()) {
    switch (*matches[1].first) {
      case '-': sign = false; break;
      case '+': sign = true; break;
    }
  }

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  if (matches[2].length()) {
    integer.append(matches[2].first, matches[2].second);
  }
  else {
    integer = "0";
  }

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  if (matches[3].length()) {
    fraction.append(matches[3].first, matches[3].second);
  }
  else {
    fraction = "0";
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////

decimal::value_type
decimal::parse(const char* literal) {
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

decimal::value_type
decimal::parse(const char* literal,
               std::error_condition& error) noexcept {
  bool sign{true};
  std::string integer, fraction;

  if (!parse_literal(literal, sign, integer, fraction)) {
    error = std::errc::invalid_argument;
    return {};
  }

  decimal::value_type result;

  errno = 0;
  result.first = std::strtoimax(integer.c_str(), nullptr, 10);
  if (errno) {
    error.assign(errno, std::generic_category());
    return {};
  }

  errno = 0;
  result.second = std::strtoimax(fraction.c_str(), nullptr, 10);
  if (errno) {
    error.assign(errno, std::generic_category());
    return {};
  }

  if (sign == false) {
    result.first = -result.first;
  }

  return result;
}

bool
decimal::match(const char* literal) noexcept {
  return *literal != '\0' && std::regex_match(literal, decimal_regex, match_not_null);
}

bool
decimal::validate() const noexcept {
  return decimal::match(_literal);
}

bool
decimal::canonicalize() noexcept {
  bool sign{true};
  std::string integer, fraction;

  if (!parse_literal(c_str(), sign, integer, fraction)) {
    throw std::invalid_argument{c_str()}; /* invalid literal */
  }

  char buffer[256] = "";
  char* output = buffer;

  /* 3.2.3.2 'The preceding optional "+" sign is prohibited' */
  if (sign == false) *output++ = '-';

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  output = std::copy(integer.cbegin(), integer.cend(), output);

  /* 3.2.3.2 'The decimal point is required' */
  *output++ = '.';

  /* 3.2.3.2 'Leading and trailing zeroes are prohibited subject to the
   * following: there must be at least one digit to the right and to the
   * left of the decimal point which may be a zero.' */
  output = std::copy(fraction.cbegin(), fraction.cend(), output);

  *output++ = '\0';

  if (_literal.compare(buffer) != 0) {
    _literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

decimal::value_type
decimal::value() const {
  return parse(c_str());
}

decimal::value_type
decimal::value(std::error_condition& error) const noexcept {
  return parse(c_str(), error);
}

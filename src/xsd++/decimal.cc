/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DECIMAL_CAPTURES */
#include "decimal.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <algorithm> /* for std::copy() */
#include <cassert>   /* for assert() */
#include <cerrno>    /* for errno */
#include <cinttypes> /* for std::strtoimax() */
#include <cstdint>   /* for std::intmax_t */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr decimal::digits_type decimal::max_integer;
constexpr decimal::scale_type  decimal::max_scale;
constexpr char                 decimal::name[];
constexpr char                 decimal::pattern[];

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

bool
decimal::validate(const char* literal) noexcept {
  return decimal::match(literal);
}

bool
decimal::match(const char* literal) noexcept {
  return *literal != '\0' && std::regex_match(literal, decimal_regex, match_not_null);
}

bool
decimal::canonicalize(std::string& literal) {
  bool sign{true};
  std::string integer, fraction;

  if (!parse_literal(literal.c_str(), sign, integer, fraction)) {
    throw std::invalid_argument{literal}; /* invalid literal */
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

  if (literal.compare(buffer) != 0) {
    literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

decimal
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

decimal
decimal::parse(const char* literal,
               std::error_condition& error) noexcept {
  bool sign{true};
  std::string integer, fraction;

  if (!parse_literal(literal, sign, integer, fraction)) {
    error = std::errc::invalid_argument;
    return {};
  }

  decimal::value_type result;

  result.sign = sign;

  if (fraction.compare("0") == 0) {
    result.scale = 0;
  }
  else {
    result.scale = fraction.size();
    integer.append(fraction);
  }

  if (result.scale > max_scale) {
    error = std::errc::result_out_of_range;
    return {};
  }

  errno = 0;
  result.digits = std::strtoimax(integer.c_str(), nullptr, 10); /* always nonnegative */
  if (errno) {
    error.assign(errno, std::generic_category());
    return {};
  }

  if (result.digits > max_integer) {
    error = std::errc::result_out_of_range;
    return {};
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////

bool
decimal::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
decimal::literal() const {
  return ""; // TODO
}

////////////////////////////////////////////////////////////////////////////////

int
decimal::compare(const decimal& other) const noexcept {
  if (value().sign != other.value().sign) {
    return !value().sign ? -1 : 1; /* negative always less than nonnegative */
  }

  auto scale = std::min(max_scale, std::max(value().scale, other.value().scale));

  digits_type value1{value().digits};
  for (auto i = 0U; i < (scale - value().scale); i++) {
    value1 *= 10;
  }

  digits_type value2{other.value().digits};
  for (auto i = 0U; i < (scale - other.value().scale); i++) {
    value2 *= 10;
  }

  if (value1 != value2) {
    return ((value1 < value2) ? -1 : 1) * (value().sign ? 1 : -1);
  }
  return 0; /* the values are equal */
}

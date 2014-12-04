/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_DOUBLE_CAPTURES */
#include "double.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <array>     /* for std::array */
#include <cassert>   /* for assert() */
#include <cerrno>    /* for ERANGE, errno */
#include <cstdlib>   /* for std::strtod() */
#include <cmath>     /* for INFINITY, NAN */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char double_::name[];

constexpr char double_::pattern[];

static const std::regex double_regex{double_::pattern};

////////////////////////////////////////////////////////////////////////////////

/**
 * @see http://www.w3.org/TR/xmlschema11-2/#double
 */
static bool
parse_literal(const char* literal,
              double& value) {

  if (*literal == '\0') {
    return false; /* invalid literal */
  }

  if (std::strcmp(literal, "INF") == 0 ||
      std::strcmp(literal, "+INF") == 0) {
    value = INFINITY;
    return true;
  }

  if (std::strcmp(literal, "-INF") == 0) {
    value = -INFINITY;
    return true;
  }

  if (std::strcmp(literal, "NaN") == 0) {
    value = NAN;
    return true;
  }

  if (!std::regex_match(literal, double_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  const char* endptr = nullptr;
  errno = 0;
  value = std::strtod(literal, (char**)&endptr);

#if 0
  if (errno == ERANGE) {
    error = std::errc::result_out_of_range;
    return value;
  }
#endif

  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool
double_::validate(const char* literal) noexcept {
  return double_::match(literal);
}

bool
double_::match(const char* literal) noexcept {
  return std::regex_match(literal, double_regex, match_not_null);
}

bool
double_::canonicalize(std::string& literal) {
  model_type value{};

  if (!parse_literal(literal.c_str(), value)) {
    throw std::invalid_argument{literal}; /* invalid literal */
  }

  std::array<char, 256> buffer;
  char* output = buffer.data();

  // TODO

  *output++ = '\0';

  if (literal.compare(buffer.data()) != 0) {
    literal.assign(buffer.data());
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

double_
double_::parse(const char* literal) {
  std::error_condition error;
  const auto result = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      if (result.value() == 0.0) {
        throw std::underflow_error{literal};
      }
      else {
        throw std::overflow_error{literal};
      }
    }
  }

  return result;
}

double_
double_::parse(const char* literal,
               std::error_condition& error) noexcept {
  model_type value{};

  if (!parse_literal(literal, value)) {
    error = std::errc::invalid_argument;
    return {};
  }

  return value;
}

////////////////////////////////////////////////////////////////////////////////

bool
double_::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
double_::literal() const {
  return std::to_string(value());
}

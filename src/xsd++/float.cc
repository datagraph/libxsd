/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_FLOAT_CAPTURES */
#include "float.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include "utility/double.h"

#include <array>     /* for std::array */
#include <cassert>   /* for assert() */
#include <cerrno>    /* for ERANGE, errno */
#include <cfloat>    /* for FLT_DIG */
#include <cstdlib>   /* for std::strtof() */
#include <cmath>     /* for INFINITY, NAN */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char float_::name[];

constexpr char float_::pattern[];

static const std::regex float_regex{float_::pattern};

////////////////////////////////////////////////////////////////////////////////

/**
 * @see http://www.w3.org/TR/xmlschema11-2/#float
 */
static bool
parse_literal(const char* literal,
              float& value) {

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

  if (!std::regex_match(literal, float_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  const char* endptr = nullptr;
  errno = 0;
  value = std::strtof(literal, (char**)&endptr);

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
float_::validate(const char* literal) noexcept {
  return float_::match(literal);
}

bool
float_::match(const char* literal) noexcept {
  return *literal != '\0' && std::regex_match(literal, float_regex, match_not_null);
}

bool
float_::canonicalize(std::string& literal) {
  model_type value{};

  if (!parse_literal(literal.c_str(), value)) {
    throw std::invalid_argument{literal}; /* invalid literal */
  }

  std::array<char, 32> buffer;
  char* output = buffer.data();

  output += format_double(static_cast<double>(value), FLT_DIG, output);

  *output++ = '\0';

  if (literal.compare(buffer.data()) != 0) {
    literal.assign(buffer.data());
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

float_
float_::parse(const char* literal) {
  std::error_condition error;
  const auto result = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      if (result.value() == 0.0f) {
        throw std::underflow_error{literal};
      }
      else {
        throw std::overflow_error{literal};
      }
    }
  }

  return result;
}

float_
float_::parse(const char* literal,
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
float_::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
float_::literal() const {
  return std::to_string(value());
}

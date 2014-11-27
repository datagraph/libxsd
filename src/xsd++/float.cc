/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h" /* for XSD_FLOAT_CAPTURES */
#include "float.h"
#include "regex.h" /* for std::regex, std::regex_match() */

#include <cerrno>  /* for ERANGE, errno */
#include <cstdlib> /* for std::strtof() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char float_::name[];

constexpr char float_::pattern[];

static const std::regex float_regex{float_::pattern};

////////////////////////////////////////////////////////////////////////////////

bool
float_::validate(const char* literal) noexcept {
  return float_::match(literal);
}

bool
float_::match(const char* literal) noexcept {
  return std::regex_match(literal, float_regex, match_not_null);
}

bool
float_::canonicalize(std::string& literal) {
  return false; // TODO
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
  if (!match(literal)) {
    error = std::errc::invalid_argument;
    return 0.0f;
  }

  const char* endptr = nullptr;
  errno = 0;
  const float value = std::strtof(literal, (char**)&endptr);

  if (errno == ERANGE) {
    error = std::errc::result_out_of_range;
    return value;
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

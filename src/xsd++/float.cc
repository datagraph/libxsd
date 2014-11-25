/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h" /* for XSD_FLOAT_CAPTURES */
#include "float.h"
#include "regex.h" /* for std::regex, std::regex_match() */

#include <cerrno>  /* for ERANGE, errno */
#include <cstdlib> /* for std::strtof() */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char float_::name[];

constexpr char float_::pattern[];

static const std::regex float_regex{float_::pattern};

bool
float_::match(const std::string& literal) noexcept {
  return std::regex_match(literal, float_regex);
}

bool
float_::validate() const noexcept {
  return float_::match(_literal);
}

bool
float_::canonicalize() noexcept {
  return false; // TODO
}

float_::operator double() const {
  return operator float();
}

float_::operator float() const {
  std::error_condition error;
  const auto value = as_float(error);

  if (error) throw std::bad_cast{};

  return value;
}

float
float_::as_float() const {
  std::error_condition error;
  const auto value = as_float(error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{c_str()};
    }
    if (error == std::errc::result_out_of_range) {
      if (value == 0.0f) {
        throw std::underflow_error{c_str()};
      }
      else {
        throw std::overflow_error{c_str()};
      }
    }
  }

  return value;
}

float
float_::as_float(std::error_condition& error) const noexcept {
  if (!validate()) {
    error = std::errc::invalid_argument;
    return 0.0f;
  }

  const char* endptr = nullptr;
  errno = 0;
  const float value = std::strtof(c_str(), (char**)&endptr);

  if (errno == ERANGE) {
    error = std::errc::result_out_of_range;
    return value;
  }

  return value;
}

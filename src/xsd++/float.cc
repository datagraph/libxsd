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

float
float_::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      if (value == 0.0f) {
        throw std::underflow_error{literal};
      }
      else {
        throw std::overflow_error{literal};
      }
    }
  }

  return value;
}

float
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

bool
float_::match(const char* literal) noexcept {
  return std::regex_match(literal, float_regex, match_not_null);
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
  const auto result = value(error);
  if (error) throw std::bad_cast{};
  return result;
}

float
float_::value() const {
  return parse(c_str());
}

float
float_::value(std::error_condition& error) const noexcept {
  return parse(c_str(), error);
}

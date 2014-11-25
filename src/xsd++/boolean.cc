/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "boolean.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <stdexcept> /* for std::invalid_argument */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char boolean::name[];

constexpr char boolean::pattern[];

static const std::regex boolean_regex{boolean::pattern};

bool
boolean::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
  }

  return value;
}

bool
boolean::parse(const char* literal,
               std::error_condition& error) noexcept {
  if (!match(literal)) {
    error = std::errc::invalid_argument;
    return false;
  }

  return std::strcmp(literal, "true") == 0 ||
         std::strcmp(literal, "1") == 0;
}

bool
boolean::match(const char* literal) noexcept {
  return std::regex_match(literal, boolean_regex, match_not_null);
}

bool
boolean::validate() const noexcept {
  return boolean::match(_literal);
}

bool
boolean::canonicalize() {
  if (_literal.compare("true") == 0) {
    return false; /* already in canonical form */
  }

  if (_literal.compare("false") == 0) {
    return false; /* already in canonical form */
  }

  if (_literal.compare("1") == 0) {
    _literal.assign("true"); /* can throw std::bad_alloc */
    return true; /* now in canonical form */
  }

  if (_literal.compare("0") == 0) {
    _literal.assign("false"); /* can throw std::bad_alloc */
    return true; /* now in canonical form */
  }

  throw std::invalid_argument{c_str()}; /* invalid literal */
}

boolean::operator bool() const {
  std::error_condition error;
  const auto result = value(error);
  if (error) throw std::bad_cast{};
  return result;
}

bool
boolean::value() const {
  return parse(c_str());
}

bool
boolean::value(std::error_condition& error) const noexcept {
  return parse(c_str(), error);
}

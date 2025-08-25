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

////////////////////////////////////////////////////////////////////////////////

bool
boolean::validate(const char* literal) {
  return boolean::match(literal);
}

bool
boolean::match(const char* literal) {
  return std::regex_match(literal, boolean_regex, match_not_null);
}

bool
boolean::canonicalize(std::string& literal) {
  if (literal.compare("true") == 0) {
    return false; /* already in canonical form */
  }

  if (literal.compare("false") == 0) {
    return false; /* already in canonical form */
  }

  if (literal.compare("1") == 0) {
    literal.assign("true"); /* can throw std::bad_alloc */
    return true; /* now in canonical form */
  }

  if (literal.compare("0") == 0) {
    literal.assign("false"); /* can throw std::bad_alloc */
    return true; /* now in canonical form */
  }

  throw std::invalid_argument{literal}; /* invalid literal */
}

boolean
boolean::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
  }

  return boolean{value};
}

boolean
boolean::parse(const char* literal,
               std::error_condition& error) {
  if (!match(literal)) {
    error = std::errc::invalid_argument;
    return boolean{false};
  }

  return boolean{std::strcmp(literal, "true") == 0 ||
                 std::strcmp(literal, "1") == 0};
}

////////////////////////////////////////////////////////////////////////////////

bool
boolean::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
boolean::literal() const {
  return {value() ? "true" : "false"};
}

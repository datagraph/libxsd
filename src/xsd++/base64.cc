/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "base64.h"
#include "regex.h"  /* for std::regex, std::regex_match() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char base64::name[];

constexpr char base64::pattern[];

static const std::regex base64_regex{base64::pattern};

////////////////////////////////////////////////////////////////////////////////

bool
base64::validate(const char* literal) {
  return base64::match(literal); // TODO: validate ASCII encoding
}

bool
base64::match(const char* literal) {
  return std::regex_match(literal, base64_regex, match_not_null);
}

bool
base64::canonicalize(std::string& literal) {
  static_cast<void>(literal);
  return false; /* already in canonical form */
}

base64
base64::parse(const char* literal) {
  return base64{literal};
}

base64
base64::parse(const char* literal,
              std::error_condition& error) {
  static_cast<void>(error);
  return base64{literal};
}

////////////////////////////////////////////////////////////////////////////////

bool
base64::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
base64::literal() const {
  return value();
}

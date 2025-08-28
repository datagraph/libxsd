/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "regex.h"  /* for std::regex, std::regex_match() */
#include "string.h"

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char string::name[];

constexpr char string::pattern[];

static const std::regex string_regex{string::pattern};

////////////////////////////////////////////////////////////////////////////////

bool
string::validate(const char* literal) {
  return string::match(literal); // TODO: validate ASCII/UTF-8 encoding
}

bool
string::match(const char* literal) {
  return std::regex_match(literal, string_regex, match_default);
}

bool
string::canonicalize(std::string& literal) {
  static_cast<void>(literal);
  return false; /* strings can't be canonicalized */
}

string
string::parse(const char* literal) {
  return string{literal};
}

string
string::parse(const char* literal,
              std::error_condition& error) {
  static_cast<void>(error);
  return string{literal};
}

////////////////////////////////////////////////////////////////////////////////

bool
string::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
string::literal() const {
  return value();
}

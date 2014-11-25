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

bool
string::match(const char* literal) noexcept {
  return std::regex_match(literal, string_regex, match_default);
}

bool
string::validate() const noexcept {
  return string::match(_literal); // TODO: validate ASCII/UTF-8 encoding
}

bool
string::canonicalize() noexcept {
  return false; /* strings can't be canonicalized */
}

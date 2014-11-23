/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "regex.h"  /* for std::regex, std::regex_match() */
#include "string.h"

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char string::name[];

constexpr char string::pattern[];

static const std::regex string_regex{string::pattern};

bool
string::match(const std::string& literal) noexcept {
  return std::regex_match(literal, string_regex);
}

bool
string::validate() const noexcept {
  return string::match(_literal);
}

bool
string::canonicalize() noexcept {
  return false; // TODO
}

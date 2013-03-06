/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/string.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex string_regex(string::pattern);

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

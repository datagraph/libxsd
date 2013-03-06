/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/integer.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex integer_regex(integer::pattern);

bool
integer::match(const std::string& literal) noexcept {
  return std::regex_match(literal, integer_regex);
}

bool
integer::validate() const noexcept {
  return true; // TODO
}

bool
integer::canonicalize() noexcept {
  return false; // TODO
}

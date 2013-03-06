/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/float.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex float_regex(float_::pattern);

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

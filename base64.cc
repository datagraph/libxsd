/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/base64.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex base64_regex(base64::pattern);

bool
base64::match(const std::string& literal) noexcept {
  return std::regex_match(literal, base64_regex);
}

bool
base64::validate() const noexcept {
  return base64::match(_literal);
}

bool
base64::canonicalize() noexcept {
  return false; // TODO
}

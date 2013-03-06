/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/time.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex time_regex(time::pattern);

bool
time::match(const std::string& literal) noexcept {
  return std::regex_match(literal, time_regex);
}

bool
time::validate() const noexcept {
  return time::match(_literal);
}

bool
time::canonicalize() noexcept {
  return false; // TODO
}

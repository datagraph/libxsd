/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/decimal.h"

#include <regex> /* for std::regex, std::regex_match() */

using namespace xsd;

static const std::regex decimal_regex(decimal::pattern);

bool
decimal::match(const std::string& literal) noexcept {
  return std::regex_match(literal, decimal_regex);
}

bool
decimal::validate() const noexcept {
  return true; // TODO
}

bool
decimal::canonicalize() noexcept {
  return false; // TODO
}

/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "decimal.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char decimal::name[];

constexpr char decimal::pattern[];

static const std::regex decimal_regex{decimal::pattern};

bool
decimal::match(const std::string& literal) noexcept {
  return std::regex_match(literal, decimal_regex);
}

bool
decimal::validate() const noexcept {
  return decimal::match(_literal);
}

bool
decimal::canonicalize() noexcept {
  return false; // TODO
}

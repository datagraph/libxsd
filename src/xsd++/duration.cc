/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "duration.h"
#include "regex.h"    /* for std::regex, std::regex_match() */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char duration::name[];

constexpr char duration::pattern[];

static const std::regex duration_regex{duration::pattern};

bool
duration::match(const std::string& literal) noexcept {
  return std::regex_match(literal, duration_regex);
}

bool
duration::validate() const noexcept {
  return duration::match(_literal);
}

bool
duration::canonicalize() noexcept {
  return false; // TODO
}

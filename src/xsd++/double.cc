/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "double.h"
#include "regex.h"  /* for std::regex, std::regex_match() */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char double_::name[];

constexpr char double_::pattern[];

static const std::regex double_regex{double_::pattern};

bool
double_::match(const std::string& literal) noexcept {
  return std::regex_match(literal, double_regex);
}

bool
double_::validate() const noexcept {
  return double_::match(_literal);
}

bool
double_::canonicalize() noexcept {
  return false; // TODO
}

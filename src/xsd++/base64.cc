/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "base64.h"
#include "regex.h"  /* for std::regex, std::regex_match() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char base64::name[];

constexpr char base64::pattern[];

static const std::regex base64_regex{base64::pattern};

bool
base64::match(const char* literal) noexcept {
  return std::regex_match(literal, base64_regex, match_not_null);
}

bool
base64::validate() const noexcept {
  return base64::match(_literal);
}

bool
base64::canonicalize() noexcept {
  return false; // TODO
}

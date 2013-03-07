/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/date.h"

#include "xsd++/regex.h" /* for std::regex, std::regex_match() */

using namespace xsd;

constexpr char date::name[];

constexpr char date::pattern[];

static const std::regex date_regex(date::pattern);

bool
date::match(const std::string& literal) noexcept {
  return std::regex_match(literal, date_regex);
}

bool
date::validate() const noexcept {
  return date::match(_literal);
}

bool
date::canonicalize() noexcept {
  return false; // TODO
}

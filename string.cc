/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/string.h"

using namespace xsd;

bool
string::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
string::validate() const noexcept {
  return true; // TODO
}

bool
string::canonicalize() noexcept {
  return false; // TODO
}

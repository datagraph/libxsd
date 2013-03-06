/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/integer.h"

using namespace xsd;

bool
integer::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
integer::validate() const noexcept {
  return true; // TODO
}

bool
integer::canonicalize() noexcept {
  return false; // TODO
}

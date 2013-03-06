/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/float.h"

using namespace xsd;

bool
float_::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
float_::validate() const noexcept {
  return true; // TODO
}

bool
float_::canonicalize() noexcept {
  return false; // TODO
}

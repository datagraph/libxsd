/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/time.h"

using namespace xsd;

bool
time::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
time::validate() const noexcept {
  return true; // TODO
}

bool
time::canonicalize() noexcept {
  return false; // TODO
}

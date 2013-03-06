/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/datetime.h"

using namespace xsd;

bool
datetime::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
datetime::validate() const noexcept {
  return true; // TODO
}

bool
datetime::canonicalize() noexcept {
  return false; // TODO
}

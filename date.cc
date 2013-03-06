/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/date.h"

using namespace xsd;

bool
date::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
date::validate() const noexcept {
  return true; // TODO
}

bool
date::canonicalize() noexcept {
  return false; // TODO
}

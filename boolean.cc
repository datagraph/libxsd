/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/boolean.h"

using namespace xsd;

bool
boolean::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
boolean::validate() const noexcept {
  return true; // TODO
}

bool
boolean::canonicalize() noexcept {
  return false; // TODO
}

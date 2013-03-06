/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/base64.h"

using namespace xsd;

bool
base64::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
base64::validate() const noexcept {
  return true; // TODO
}

bool
base64::canonicalize() noexcept {
  return false; // TODO
}

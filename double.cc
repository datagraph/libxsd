/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/double.h"

using namespace xsd;

bool
double_::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
double_::validate() const noexcept {
  return true; // TODO
}

bool
double_::canonicalize() noexcept {
  return false; // TODO
}

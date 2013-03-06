/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xsd++/decimal.h"

using namespace xsd;

bool
decimal::match(const std::string& literal) noexcept {
  return (void)literal, false; // TODO
}

bool
decimal::validate() const noexcept {
  return true; // TODO
}

bool
decimal::canonicalize() noexcept {
  return false; // TODO
}

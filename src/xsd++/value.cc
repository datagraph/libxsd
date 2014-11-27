/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "value.h"

#include <typeinfo> /* for std::bad_cast */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

value::operator bool() const {
  throw std::bad_cast{};
}

value::operator int() const {
  throw std::bad_cast{};
}

value::operator long() const {
  throw std::bad_cast{};
}

value::operator long long() const {
  throw std::bad_cast{};
}

value::operator double() const {
  throw std::bad_cast{};
}

value::operator float() const {
  throw std::bad_cast{};
}

value::operator std::string() const {
  return literal();
}

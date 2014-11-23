/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "base64.h"   /* for xsd::base64   */
#include "boolean.h"  /* for xsd::boolean  */
#include "date.h"     /* for xsd::date     */
#include "datetime.h" /* for xsd::datetime */
#include "decimal.h"  /* for xsd::decimal  */
#include "double.h"   /* for xsd::double   */
#include "duration.h" /* for xsd::duration */
#include "extern.h"   /* for xsd_*()       */
#include "float.h"    /* for xsd::float    */
#include "integer.h"  /* for xsd::integer  */
#include "string.h"   /* for xsd::string   */
#include "time.h"     /* for xsd::time     */

#include <cassert>    /* for assert() */
#include <cstring>    /* for strdup() */

////////////////////////////////////////////////////////////////////////////////

template<typename T>
static bool
canonicalize(char** literal) {
  T value{*literal};
  if (value.canonicalize()) {
    free(*literal);
    *literal = strdup(value.c_str());
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_base64_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::base64{literal}.validate();
}

bool
xsd_base64_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::base64>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_boolean_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::boolean{literal}.validate();
}

bool
xsd_boolean_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::boolean>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_date_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::date{literal}.validate();
}

bool
xsd_date_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::date>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_datetime_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::datetime{literal}.validate();
}

bool
xsd_datetime_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::datetime>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_decimal_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::decimal{literal}.validate();
}

bool
xsd_decimal_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::decimal>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_double_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::double_{literal}.validate();
}

bool
xsd_double_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::double_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_duration_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::duration{literal}.validate();
}

bool
xsd_duration_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::duration>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_float_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::float_{literal}.validate();
}

bool
xsd_float_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::float_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_integer_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::integer{literal}.validate();
}

bool
xsd_integer_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::integer>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_string_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::string{literal}.validate();
}

bool
xsd_string_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::string>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_time_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::time{literal}.validate();
}

bool
xsd_time_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::time>(literal);
}

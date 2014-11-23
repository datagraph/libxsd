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

////////////////////////////////////////////////////////////////////////////////

bool
xsd_base64_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::base64{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_boolean_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::boolean{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_datetime_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::datetime{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_date_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::date{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_decimal_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::decimal{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_double_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::double_{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_duration_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::duration{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_float_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::float_{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_integer_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::integer{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_string_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::string{literal}.validate();
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_time_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::time{literal}.validate();
}

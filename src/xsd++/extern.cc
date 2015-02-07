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

#include <cassert>    /* for assert()  */
#include <cerrno>     /* for E*, errno */
#include <cstring>    /* for strdup()  */
#include <new>        /* for std::bad_alloc */
#include <stdexcept>  /* for std::invalid_argumen */
#include <typeinfo>   /* for std::bad_cast */

////////////////////////////////////////////////////////////////////////////////

template<typename T>
static bool
canonicalize(char** literal) {
  try {
    std::string buffer{*literal};
    if (T::canonicalize(buffer)) {
      free(*literal);
      *literal = strdup(buffer.c_str());
      return true;
    }
  }
  catch (const std::bad_alloc& error) {
    errno = ENOMEM; /* Out of memory (POSIX.1) */
  }
  catch (const std::invalid_argument& error) {
    errno = EINVAL; /* Invalid argument (POSIX.1) */
  }
  catch (...) {
    errno = ECANCELED; /* Operation canceled (POSIX.1) */
  }
  return false;
}

template<typename T, typename U>
static T
safe_cast(const char* literal) {
  try {
    std::error_condition error;
    const auto value = static_cast<T>(U::parse(literal, error));
    if (error) {
      if (error == std::errc::invalid_argument) {
        errno = EINVAL; /* Invalid argument (POSIX.1) */
      }
      else if (error == std::errc::result_out_of_range) {
        errno = ERANGE; /* Numerical result out of range (POSIX.1, C99) */
      }
    }
    return value;
  }
  catch (...) {
    errno = ECANCELED; /* Operation canceled (POSIX.1) */
  }
  return static_cast<T>(0);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_base64_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::base64::validate(literal);
}

bool
xsd_base64_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::base64>(literal);
}

const char*
xsd_base64_value(const char* literal) {
  assert(literal != nullptr);

  return literal;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_boolean_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::boolean::validate(literal);
}

bool
xsd_boolean_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::boolean>(literal);
}

bool
xsd_boolean_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<bool, xsd::boolean>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_date_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::date::validate(literal);
}

bool
xsd_date_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::date>(literal);
}

int64_t
xsd_date_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::date>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_datetime_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::datetime::validate(literal);
}

bool
xsd_datetime_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::datetime>(literal);
}

int64_t
xsd_datetime_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::datetime>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_decimal_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::decimal::validate(literal);
}

bool
xsd_decimal_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::decimal>(literal);
}

double
xsd_decimal_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<double, xsd::decimal>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_double_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::double_::validate(literal);
}

bool
xsd_double_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::double_>(literal);
}

double
xsd_double_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<double, xsd::double_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_duration_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::duration::validate(literal);
}

bool
xsd_duration_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::duration>(literal);
}

// TODO: xsd_duration_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool
xsd_float_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::float_::validate(literal);
}

bool
xsd_float_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::float_>(literal);
}

float
xsd_float_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<float, xsd::float_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_integer_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::integer::validate(literal);
}

bool
xsd_integer_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::integer>(literal);
}

std::intmax_t
xsd_integer_value(const char* literal,
                  const std::intmax_t min_value,
                  const std::intmax_t max_value) {
  assert(literal != nullptr);

  std::error_condition error;
  const auto value = xsd::integer::parse(literal, min_value, max_value, error).value();
  if (error) errno = error.value();
  return value;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_string_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::string::validate(literal);
}

bool
xsd_string_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::string>(literal);
}

const char*
xsd_string_value(const char* literal) {
  assert(literal != nullptr);

  return literal;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_time_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::time::validate(literal);
}

bool
xsd_time_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::time>(literal);
}

int64_t
xsd_time_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::time>(literal);
}

/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_EXTERN_H
#define XSDXX_EXTERN_H

#include <stdbool.h> /* for bool */
#include <stdint.h>  /* for int*_t, uint*_t */

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////

bool xsd_base64_validate(const char* literal);

bool xsd_base64_canonicalize(char** literal);

const char* xsd_base64_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_boolean_validate(const char* literal);

bool xsd_boolean_canonicalize(char** literal);

bool xsd_boolean_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_date_validate(const char* literal);

bool xsd_date_canonicalize(char** literal);

int64_t xsd_date_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_datetime_validate(const char* literal);

bool xsd_datetime_canonicalize(char** literal);

int64_t xsd_datetime_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_decimal_validate(const char* literal);

bool xsd_decimal_canonicalize(char** literal);

double xsd_decimal_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_double_validate(const char* literal);

bool xsd_double_canonicalize(char** literal);

double xsd_double_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_duration_validate(const char* literal);

bool xsd_duration_canonicalize(char** literal);

// TODO: xsd_duration_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_float_validate(const char* literal);

bool xsd_float_canonicalize(char** literal);

float xsd_float_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_integer_validate(const char* literal);

bool xsd_integer_canonicalize(char** literal);

intmax_t xsd_integer_value(const char* literal, intmax_t min_value, intmax_t max_value);

static inline int8_t xsd_int8_value(const char* literal) {
  return (int8_t)xsd_integer_value(literal, INT8_MIN, INT8_MAX);
}

static inline int16_t xsd_int16_value(const char* literal) {
  return (int16_t)xsd_integer_value(literal, INT16_MIN, INT16_MAX);
}

static inline int32_t xsd_int32_value(const char* literal) {
  return (int32_t)xsd_integer_value(literal, INT32_MIN, INT32_MAX);
}

static inline int64_t xsd_int64_value(const char* literal) {
  return (int64_t)xsd_integer_value(literal, INT64_MIN, INT64_MAX);
}

static inline intmax_t xsd_intmax_value(const char* literal) {
  return (intmax_t)xsd_integer_value(literal, INTMAX_MIN, INTMAX_MAX);
}

static inline uint8_t xsd_uint8_value(const char* literal) {
  return (uint8_t)xsd_integer_value(literal, 0, UINT8_MAX);
}

static inline uint16_t xsd_uint16_value(const char* literal) {
  return (uint16_t)xsd_integer_value(literal, 0, UINT16_MAX);
}

static inline uint32_t xsd_uint32_value(const char* literal) {
  return (uint32_t)xsd_integer_value(literal, 0, UINT32_MAX);
}

static inline uint64_t xsd_uint64_value(const char* literal) {
  return (uint64_t)xsd_integer_value(literal, 0, UINT64_MAX);
}

static inline uintmax_t xsd_uintmax_value(const char* literal) {
  return (uintmax_t)xsd_integer_value(literal, 0, INTMAX_MAX);
}

////////////////////////////////////////////////////////////////////////////////

bool xsd_string_validate(const char* literal);

bool xsd_string_canonicalize(char** literal);

const char* xsd_string_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool xsd_time_validate(const char* literal);

bool xsd_time_canonicalize(char** literal);

int64_t xsd_time_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* XSDXX_EXTERN_H */

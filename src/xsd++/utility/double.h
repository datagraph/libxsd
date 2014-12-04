/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_UTILITY_DOUBLE_H
#define XSDXX_UTILITY_DOUBLE_H

#include <array>   /* for std::array */
#include <cassert> /* for assert() */
#include <cmath>   /* for std::isinf(), std::isnan() */

////////////////////////////////////////////////////////////////////////////////

namespace {
  static int format_double(const double input,
                           const int precision,
                           char* const output) {

    if (std::isnan(input)) {
      return std::sprintf(output, "NaN");
    }

    if (std::isinf(input)) {
      return std::sprintf(output, "%s%s", (input < 0) ? "-" : "", "INF");
    }

    std::array<char, 32> buffer;
    std::sprintf(buffer.data(), "%+1.*E", precision, input);

    int integral = 0;
    unsigned long fraction = 0;
    int exponent = 0;
    const int rc = std::sscanf(buffer.data(), "%d.%luE%d", &integral, &fraction, &exponent);
    assert(rc == 3); static_cast<void>(rc);
    assert(integral > -10 && integral < 10);

    const char* leading_zeroes = "";
    if (fraction != 0) {
      char* p = buffer.data();
      while (*p++ != '.');   /* find the decimal point */
      leading_zeroes = p;
      while (*p == '0') p++; /* find the first non-zero character */
      *p = '\0';             /* null-terminate the buffer after leading zeroes */
    }

    while (fraction > 0 && fraction % 10 == 0) {
      fraction /= 10; /* trim trailing zeroes */
    }

    return std::sprintf(output, "%1d.%s%luE%d", integral, leading_zeroes, fraction, exponent);
  }
}

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_UTILITY_DOUBLE_H */

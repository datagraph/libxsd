/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_UTILITY_INTEGER_H
#define XSDXX_UTILITY_INTEGER_H

#include "../regex.h" /* for std::csub_match */

#include <algorithm>  /* for std::copy_n() */
#include <cassert>    /* for assert() */
#include <cstddef>    /* for std::size_t */
#include <cstdlib>    /* for std::atol() */

////////////////////////////////////////////////////////////////////////////////

namespace {
  template<typename T>
  static T parse_integer(const std::csub_match& match,
                         const std::size_t offset = 0) {
    assert(offset <= match.length());

    const auto length = match.length() - offset;

    char buffer[length + 1];
    *std::copy_n(match.first + offset, length, buffer) = '\0';

    return static_cast<T>(std::atol(buffer));
  }
}

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_UTILITY_INTEGER_H */

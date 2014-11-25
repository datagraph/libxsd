/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h"   /* for XSD_INTEGER_CAPTURES */
#include "integer.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <algorithm> /* for std::copy() */
#include <cassert>   /* for assert() */
#include <cerrno>    /* for errno */
#include <cinttypes> /* for std::strtoimax() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char integer::name[];

constexpr char integer::pattern[];

static const std::regex integer_regex{integer::pattern};

bool
integer::match(const char* literal) noexcept {
  return std::regex_match(literal, integer_regex, match_not_null);
}

bool
integer::validate() const noexcept {
  return integer::match(_literal);
}

bool
integer::canonicalize() noexcept {
  std::cmatch matches;
  if (!std::regex_match(c_str(), matches, integer_regex, match_not_null)) {
    throw std::invalid_argument{c_str()}; /* invalid literal */
  }

  assert(matches.size() == XSD_INTEGER_CAPTURES);

  char buffer[256] = "";
  char* output = buffer;

  /* 3.3.13.2 'The preceding optional "+" sign is prohibited' */
  if (matches[1].length()) {
    const char sign = *matches[1].first;
    if (sign == '-') {
      *output++ = sign;
    }
  }

  /* 3.3.13.2 'Leading zeroes are prohibited' */
  {
    output = std::copy(matches[2].first, matches[2].second, output);
  }

  *output++ = '\0';

  if (_literal.compare(buffer) != 0) {
    _literal.assign(buffer);
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

std::intmax_t
integer::as_integer(const std::intmax_t min_value,
                    const std::intmax_t max_value) const {
  errno = 0;
  const auto value = std::strtoimax(c_str(), nullptr, 10);

  if (errno == EINVAL) {
    throw std::bad_cast{};
  }

  if ((errno == ERANGE && value == INTMAX_MIN) || value < min_value) {
    throw std::underflow_error{c_str()};
  }

  if ((errno == ERANGE && value == INTMAX_MAX) || value > max_value) {
    throw std::overflow_error{c_str()};
  }

  return value;
}

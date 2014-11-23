/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "integer.h"
#include "regex.h"   /* for std::regex, std::regex_match() */

#include <cerrno>    /* for errno */
#include <cinttypes> /* for std::strtoimax() */

using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char integer::name[];

constexpr char integer::pattern[];

static const std::regex integer_regex{integer::pattern};

bool
integer::match(const std::string& literal) noexcept {
  return std::regex_match(literal, integer_regex);
}

bool
integer::validate() const noexcept {
  return integer::match(_literal);
}

bool
integer::canonicalize() noexcept {
  return false; // TODO
}

std::intmax_t
integer::as_integer(const std::intmax_t min_value,
                    const std::intmax_t max_value) const {
  errno = 0;
  const auto value = std::strtoimax(_literal.c_str(), nullptr, 10);

  if (errno == EINVAL) {
    throw std::bad_cast{};
  }

  if ((errno == ERANGE && value == INTMAX_MIN) || value < min_value) {
    throw std::underflow_error{_literal.c_str()};
  }

  if ((errno == ERANGE && value == INTMAX_MAX) || value > max_value) {
    throw std::overflow_error{_literal.c_str()};
  }

  return value;
}

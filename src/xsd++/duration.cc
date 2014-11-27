/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "duration.h"
#include "regex.h"    /* for std::regex, std::regex_match() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char duration::name[];

constexpr char duration::pattern[];

static const std::regex duration_regex{duration::pattern};

////////////////////////////////////////////////////////////////////////////////

bool
duration::validate(const char* literal) noexcept {
  return duration::match(literal);
}

bool
duration::match(const char* literal) noexcept {
  return std::regex_match(literal, duration_regex, match_not_null);
}

bool
duration::canonicalize(std::string& literal) {
  return false; // TODO
}

duration
duration::parse(const char* literal) {
  return duration{}; // TODO
}

duration
duration::parse(const char* literal,
                std::error_condition& error) noexcept {
  static_cast<void>(error);
  return duration{}; // TODO
}

////////////////////////////////////////////////////////////////////////////////

bool
duration::normalize() noexcept {
  return false; /* already in normal form */
}

std::string
duration::literal() const {
  return ""; // TODO
}

duration::model_type
duration::model() const {
  return {}; // TODO
}

/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "duration.h"
#include "regex.h"    /* for std::regex, std::regex_match() */

#include <array>      /* for std::array */
#include <cassert>    /* for assert() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char duration::name[];

constexpr char duration::pattern[];

static const std::regex duration_regex{duration::pattern};

////////////////////////////////////////////////////////////////////////////////

/**
 * @see http://www.w3.org/TR/xmlschema11-2/#nt-timeRep
 */
static bool
parse_literal(const char* literal,
              xsd::duration::model_type& /*value*/) {

  std::cmatch matches;
  if (!std::regex_match(literal, matches, duration_regex, match_not_null)) {
    return false; /* invalid literal */
  }

  assert(matches.size() == xsd::duration::captures);

  // TODO

  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool
duration::validate(const char* literal) {
  return duration::match(literal);
}

bool
duration::match(const char* literal) {
  return std::regex_match(literal, duration_regex, match_not_null);
}

bool
duration::canonicalize(std::string& literal) {
  model_type value{};

  if (!parse_literal(literal.c_str(), value)) {
    throw std::invalid_argument{literal}; /* invalid literal */
  }

  std::array<char, 256> buffer;
  char* output = buffer.data();

  // TODO

  *output++ = '\0';

  if (literal.compare(buffer.data()) != 0) {
    literal.assign(buffer.data());
    return true; /* now in canonical form */
  }

  return false; /* already in canonical form */
}

duration
duration::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      throw std::overflow_error{literal};
    }
  }

  return value;
}

duration
duration::parse(const char* literal,
                std::error_condition& error) {
  model_type value{};

  if (!parse_literal(literal, value)) {
    error = std::errc::invalid_argument;
    return {};
  }

  return value;
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

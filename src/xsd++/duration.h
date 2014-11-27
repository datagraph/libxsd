/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DURATION_H
#define XSDXX_DURATION_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class duration;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::duration : public xsd::value {
public:
  using value_type = std::int64_t;
  using model_type = value_type;

  static constexpr char name[]    = "duration";
  static constexpr char pattern[] = ".*$"; // TODO
  static constexpr bool captures  = 0;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  duration(const std::string& literal)
    : xsd::value{literal} {}

  duration(const char* literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DURATION_H */

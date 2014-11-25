/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_FLOAT_H
#define XSDXX_FLOAT_H

#include "value.h"

#include <string> /* for std::to_string() */

namespace xsd {
  class float_;
}

class xsd::float_ : public xsd::value {
public:
  using value_type = float;

  static constexpr char name[]    = "float";
  static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$";
  static constexpr bool captures  = 6;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  float_(float literal)
    : xsd::value{std::to_string(literal)} {}

  float_(double literal)
    : xsd::value{std::to_string(static_cast<float>(literal))} {}

  float_(long double literal)
    : xsd::value{std::to_string(static_cast<float>(literal))} {}

  float_(const std::string& literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  virtual explicit operator double() const override;

  virtual explicit operator float() const override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

#endif /* XSDXX_FLOAT_H */

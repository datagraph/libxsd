/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_BOOLEAN_H
#define XSDXX_BOOLEAN_H

#include "value.h"

namespace xsd {
  class boolean;
}

class xsd::boolean : public xsd::value {
public:
  using value_type = bool;

  static constexpr char name[]    = "boolean";
  static constexpr char pattern[] = "^(true|false|1|0)$";
  static constexpr bool captures  = 1;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  explicit boolean(bool literal)
    : xsd::value{literal ? "true" : "false"} {}

  boolean(const std::string& literal)
    : xsd::value{literal} {}

  boolean(const char* literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() override;

  virtual explicit operator bool() const override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

#endif /* XSDXX_BOOLEAN_H */

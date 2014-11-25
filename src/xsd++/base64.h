/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_BASE64_H
#define XSDXX_BASE64_H

#include "value.h"

namespace xsd {
  class base64;
}

class xsd::base64 : public xsd::value {
public:
  using value_type = std::string;

  static constexpr char name[]    = "base64Binary";
  static constexpr char pattern[] = "^(.*)$"; // TODO
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

  base64(const std::string& literal)
    : xsd::value{literal} {}

  base64(const char* literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

#endif /* XSDXX_BASE64_H */

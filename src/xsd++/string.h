/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_STRING_H
#define XSDXX_STRING_H

#include "value.h"

namespace xsd {
  class string;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::string : public xsd::value {
public:
  using value_type = std::string;
  using model_type = value_type;

  static constexpr char name[]    = "string";
  static constexpr char pattern[] = "^(.*)$";
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

  string(const std::string& literal)
    : xsd::value{literal} {}

  string(const char* literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_STRING_H */

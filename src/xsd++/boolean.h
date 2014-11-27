/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_BOOLEAN_H
#define XSDXX_BOOLEAN_H

#include "value.h"

namespace xsd {
  class boolean;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::boolean : public xsd::value {
public:
  using value_type = bool;
  using model_type = value_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "boolean";
  static constexpr char pattern[] = "^(true|false|1|0)$";
  static constexpr bool captures  = 1;

  /**
   * @copydoc xsd::value::validate(std::string&)
   */
  static bool validate(const std::string& literal) noexcept {
    return validate(literal.c_str());
  }

  /**
   * @copydoc xsd::value::validate(const char*)
   */
  static bool validate(const char* literal) noexcept;

  /**
   * @copydoc xsd::value::match(std::string&)
   */
  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  /**
   * @copydoc xsd::value::match(const char*)
   */
  static bool match(const char* literal) noexcept;

  static bool canonicalize(std::string& literal);

  static boolean parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static boolean parse(const char* literal);

  static boolean parse(const char* literal, std::error_condition& error) noexcept;

  boolean() noexcept = default;

  explicit boolean(const bool value) noexcept
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual explicit operator bool() const override {
    return value();
  }

  virtual std::string literal() const override;

  value_type value() const noexcept {
    return _value;
  }

  model_type model() const noexcept {
    return _value;
  }
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_BOOLEAN_H */

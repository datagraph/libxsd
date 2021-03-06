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

protected:
  value_type _value;

public:
  static constexpr char name[]    = "string";
  static constexpr char pattern[] = "^(.*)$";
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

  static string parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static string parse(const char* literal);

  static string parse(const char* literal, std::error_condition& error) noexcept;

  string() = default;

  string(const std::string& value)
    : _value{value} {}

  string(const char* value)
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual std::string literal() const override;

  const value_type& value() const noexcept {
    return _value;
  }

  const model_type& model() const noexcept {
    return _value;
  }
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_STRING_H */

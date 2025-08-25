/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_FLOAT_H
#define XSDXX_FLOAT_H

#include "value.h"
#include "const.h"

#include <string> /* for std::to_string() */

namespace xsd {
  class float_;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::float_ : public xsd::value {
public:
  using value_type = float;
  using model_type = value_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "float";
  static constexpr char pattern[] = XSD_FLOAT_PATTERN;
  static constexpr bool captures  = 6;

  /**
   * @copydoc xsd::value::validate(std::string&)
   */
  static bool validate(const std::string& literal) {
    return validate(literal.c_str());
  }

  /**
   * @copydoc xsd::value::validate(const char*)
   */
  static bool validate(const char* literal);

  /**
   * @copydoc xsd::value::match(std::string&)
   */
  static bool match(const std::string& literal) {
    return match(literal.c_str());
  }

  /**
   * @copydoc xsd::value::match(const char*)
   */
  static bool match(const char* literal);

  static bool canonicalize(std::string& literal);

  static float_ parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static float_ parse(const char* literal);

  static float_ parse(const char* literal, std::error_condition& error);

  float_() = default;

  float_(const float value)
    : _value{value} {}

  float_(const double value)
    : _value{static_cast<float>(value)} {}

  float_(const long double value)
    : _value{static_cast<float>(value)} {}

  virtual bool normalize() noexcept override;

  virtual explicit operator double() const override {
    return operator float();
  }

  virtual explicit operator float() const override {
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

#endif /* XSDXX_FLOAT_H */

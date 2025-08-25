/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DOUBLE_H
#define XSDXX_DOUBLE_H

#include "value.h"

#include <string> /* for std::to_string() */

namespace xsd {
  class double_;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::double_ : public xsd::value {
public:
  using value_type = double;
  using model_type = value_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "double";
  static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$";
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

  static double_ parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static double_ parse(const char* literal);

  static double_ parse(const char* literal, std::error_condition& error);

  double_() = default;

  double_(const float value)
    : _value{value} {}

  double_(const double value)
    : _value{value} {}

  double_(const long double value)
    : _value{static_cast<double>(value)} {}

  virtual bool normalize() noexcept override;

  virtual explicit operator double() const override {
    return value();
  }

  virtual explicit operator float() const override {
    return operator double(); /* loss of precision */
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

#endif /* XSDXX_DOUBLE_H */

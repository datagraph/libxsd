/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_INTEGER_H
#define XSDXX_INTEGER_H

#include "value.h"

#include <cstdint> /* for std::intmax_t */
#include <string>  /* for std::to_string() */

namespace xsd {
  class integer;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::integer : public xsd::value {
public:
  using value_type = std::intmax_t;
  using model_type = value_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "integer";
  static constexpr char pattern[] = "^([-+])?0*([0-9]+)$";
  static constexpr bool captures  = 3;

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

  static integer parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static integer parse(const char* literal);

  static integer parse(const char* literal, std::error_condition& error) noexcept;

  static integer parse(const char* literal,
    value_type min_value,
    value_type max_value,
    std::error_condition& error) noexcept;

  integer() noexcept = default;

  integer(const value_type value) noexcept
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual explicit operator long long() const override {
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

#endif /* XSDXX_INTEGER_H */

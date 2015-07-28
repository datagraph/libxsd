/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DECIMAL_H
#define XSDXX_DECIMAL_H

#include "value.h"

#include <cstddef> /* for std::size_t */
#include <cstdint> /* for std::intmax_t, std::uint8_t */
#include <limits>  /* for std::numeric_limits */
#include <string>  /* for std::to_string() */
#include <utility> /* for std::pair */

namespace xsd {
  class decimal;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::decimal : public xsd::value {
public:
  static constexpr std::size_t max_scale = 20; /* 2^64 */

  struct model_type final {
    std::intmax_t integer;
    std::uint8_t scale;     /** The number of fractional digits. */
  };
  using value_type = model_type;

  bool sign() const noexcept {
    return (value().integer >= 0);
  }

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "decimal";
  static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[1-9]*)0*$";
  static constexpr bool captures  = 4;

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

  static bool canonicalize(std::string& literal);

  static decimal parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static decimal parse(const char* literal);

  static decimal parse(const char* literal, std::error_condition& error) noexcept;

  /**
   * @copydoc xsd::value::match(const char*)
   */
  static bool match(const char* literal) noexcept;

  decimal() noexcept = default;

  decimal(const value_type value) noexcept
    : _value{value.integer, value.scale} {}

  virtual bool normalize() noexcept override;

  virtual explicit operator double() const override {
    return 0.0; // TODO
  }

  virtual explicit operator float() const override {
    return 0.0f; // TODO
  }

  virtual std::string literal() const override;

  const value_type& value() const noexcept {
    return _value;
  }

  const model_type& model() const noexcept {
    return _value;
  }

  int compare(const decimal& other) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DECIMAL_H */

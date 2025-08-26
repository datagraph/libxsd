/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DECIMAL_H
#define XSDXX_DECIMAL_H

#include "value.h"
#include "const.h"

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
  using digits_type = std::uintmax_t;
  using scale_type  = std::uint8_t;

  static constexpr digits_type max_integer = std::numeric_limits<digits_type>::max();
  static constexpr scale_type  max_scale   = 19; /* safe limit for 2^64 representation */

  struct model_type final {
    digits_type digits;         /** The unsigned integer digits */
    scale_type scale;           /** The number of fractional digits (0..max_scale) */
    bool sign;                  /** The sign of the decimal, negative or positive */
  };
  using value_type = model_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "decimal";
  static constexpr char pattern[] = XSD_DECIMAL_PATTERN;
  static constexpr bool captures  = XSD_DECIMAL_CAPTURES;

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

  static bool canonicalize(std::string& literal);

  static decimal parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static decimal parse(const char* literal);

  static decimal parse(const char* literal, std::error_condition& error);

  /**
   * @copydoc xsd::value::match(const char*)
   */
  static bool match(const char* literal);

  decimal() = default;

  decimal(const value_type value)
    : _value{value.digits, value.scale, value.sign} {}

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

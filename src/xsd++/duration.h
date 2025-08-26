/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DURATION_H
#define XSDXX_DURATION_H

#include "value.h"
#include "const.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class duration;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::duration : public xsd::value {
public:
  using value_type = std::int64_t;
  using model_type = value_type;

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "duration";
  static constexpr char pattern[] = XSD_DURATION_PATTERN;
  static constexpr bool captures  = XSD_DURATION_CAPTURES;       // TODO

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

  static duration parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static duration parse(const char* literal);

  static duration parse(const char* literal, std::error_condition& error);

  duration() = default;

  duration(const value_type value)
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual std::string literal() const override;

  value_type value() const noexcept {
    return _value;
  }

  model_type model() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DURATION_H */

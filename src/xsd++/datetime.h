/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATETIME_H
#define XSDXX_DATETIME_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class datetime;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::datetime : public xsd::value {
public:
  using value_type = std::int64_t;

  /**
   * @see http://www.w3.org/TR/xmlschema11-2/#dt-dt-7PropMod
   */
  struct model_type final {
    signed int year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned int microsecond;
    bool tz;
    signed short tz_hour;
    unsigned short tz_minute;
  };

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "dateTime";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$";
  static constexpr bool captures  = 10;

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

  static datetime parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static datetime parse(const char* literal);

  static datetime parse(const char* literal, std::error_condition& error) noexcept;

  datetime() noexcept = default;

  datetime(const value_type value) noexcept
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual std::string literal() const override;

  value_type value() const noexcept {
    return _value;
  }

  model_type model() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DATETIME_H */

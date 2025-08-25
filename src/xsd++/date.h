/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATE_H
#define XSDXX_DATE_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class date;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::date : public xsd::value {
public:
  using value_type = std::int64_t;

  /**
   * @see http://www.w3.org/TR/xmlschema11-2/#dt-dt-7PropMod
   */
  struct model_type final {
    signed int year;
    unsigned short month;
    unsigned short day;
    bool tz;
    signed short tz_hour;
    unsigned short tz_minute;
  };

protected:
  value_type _value{};

public:
  static constexpr char name[]    = "date";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})(Z|([-+][0-9]{2}:[0-9]{2}))?$";
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

  static date parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static date parse(const char* literal);

  static date parse(const char* literal, std::error_condition& error);

  date() = default;

  date(const value_type value)
    : _value{value} {}

  virtual bool normalize() noexcept override;

  virtual std::string literal() const override;

  value_type value() const noexcept {
    return _value;
  }

  model_type model() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DATE_H */

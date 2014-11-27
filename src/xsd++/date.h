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

  static constexpr char name[]    = "date";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})(Z|([-+][0-9]{2}:[0-9]{2}))?$";
  static constexpr bool captures  = 6;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  date(const std::string& literal)
    : xsd::value{literal} {}

  date(const char* literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_DATE_H */

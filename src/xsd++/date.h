/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATE_H
#define XSDXX_DATE_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class date;
}

class xsd::date : public xsd::value {
public:
  using value_type = std::int64_t;

  static constexpr char name[]    = "date";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})(Z|([-+][0-9]{2}:[0-9]{2}))?$";
  static constexpr bool captures  = 6;

  static bool match(const std::string& literal) noexcept;

  date(const std::string& literal)
    : value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;
};

#endif /* XSDXX_DATE_H */

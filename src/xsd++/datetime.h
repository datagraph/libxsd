/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATETIME_H
#define XSDXX_DATETIME_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class datetime;
}

class xsd::datetime : public xsd::value {
public:
  using value_type = std::int64_t;

  static constexpr char name[]    = "dateTime";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$";
  static constexpr bool captures  = 10;

  static bool match(const std::string& literal) noexcept;

  datetime(const std::string& literal)
    : value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;
};

#endif /* XSDXX_DATETIME_H */

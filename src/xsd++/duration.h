/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DURATION_H
#define XSDXX_DURATION_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class duration;
}

class xsd::duration : public xsd::value {
public:
  using value_type = std::int64_t;

  static constexpr char name[]    = "duration";
  static constexpr char pattern[] = ".*$"; // TODO
  static constexpr bool captures  = 0;

  static bool match(const std::string& literal) noexcept;

  duration(const std::string& literal)
    : value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;
};

#endif /* XSDXX_DURATION_H */

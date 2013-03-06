/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DECIMAL_H
#define XSDXX_DECIMAL_H

#include "xsd++/value.h"

namespace xsd {
  class decimal : public value {
    public:
      static constexpr char name[]    = "decimal";
      static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[1-9]*)0*$";
      static constexpr bool captures  = 4;

      static bool match(const std::string& literal) noexcept;

      decimal(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_DECIMAL_H */

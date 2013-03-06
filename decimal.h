/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DECIMAL_H
#define XSDXX_DECIMAL_H

#include "xsd++/value.h"

namespace xsd {
  class decimal : public value {
    public:
      static bool match(const std::string& literal) noexcept;

      decimal(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_DECIMAL_H */

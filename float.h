/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_FLOAT_H
#define XSDXX_FLOAT_H

#include "xsd++/value.h"

namespace xsd {
  class float_ : public value {
    public:
      static bool match(const std::string& literal) noexcept;

      float_(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_FLOAT_H */

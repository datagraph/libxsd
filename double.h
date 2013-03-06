/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DOUBLE_H
#define XSDXX_DOUBLE_H

#include "xsd++/value.h"

namespace xsd {
  class double_ : public value {
    public:
      static constexpr char name[]    = "double";
      static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$";
      static constexpr bool captures  = 6;

      static bool match(const std::string& literal) noexcept;

      double_(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_DOUBLE_H */

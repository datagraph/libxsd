/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_FLOAT_H
#define XSDXX_FLOAT_H

#include <string> /* for std::to_string() */

#include "xsd++/value.h"

namespace xsd {
  class float_ : public value {
    public:
      static constexpr char name[]    = "float";
      static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$";
      static constexpr bool captures  = 6;

      static bool match(const std::string& literal) noexcept;

      float_(float literal)
        : value(std::to_string(literal)) {}

      float_(double literal)
        : value(std::to_string(static_cast<float>(literal))) {}

      float_(long double literal)
        : value(std::to_string(static_cast<float>(literal))) {}

      float_(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_FLOAT_H */

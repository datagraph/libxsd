/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_INTEGER_H
#define XSDXX_INTEGER_H

#include "xsd++/value.h"

namespace xsd {
  class integer : public value {
    public:
      static constexpr char name[]    = "integer";
      static constexpr char pattern[] = "^([-+])?0*([0-9]+)$";
      static constexpr bool captures  = 3;

      static bool match(const std::string& literal) noexcept;

      integer(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_INTEGER_H */

/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_STRING_H
#define XSDXX_STRING_H

#include "xsd++/value.h"

namespace xsd {
  class string : public value {
    public:
      static constexpr char name[]    = "string";
      static constexpr char pattern[] = "^(.*)$";
      static constexpr bool captures  = 1;

      static bool match(const std::string& literal) noexcept;

      string(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_STRING_H */
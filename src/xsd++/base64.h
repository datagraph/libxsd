/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_BASE64_H
#define XSDXX_BASE64_H

#include "xsd++/value.h"

namespace xsd {
  class base64 : public value {
    public:
      static constexpr char name[]    = "base64Binary";
      static constexpr char pattern[] = "^(.*)$"; // TODO
      static constexpr bool captures  = 1;

      static bool match(const std::string& literal) noexcept;

      base64(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_BASE64_H */

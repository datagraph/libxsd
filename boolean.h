/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_BOOLEAN_H
#define XSDXX_BOOLEAN_H

#include "xsd++/value.h"

namespace xsd {
  class boolean : public value {
    public:
      static constexpr char name[]    = "boolean";
      static constexpr char pattern[] = "^(true|false|1|0)$";
      static constexpr bool captures  = 1;

      static bool match(const std::string& literal) noexcept;

      boolean(bool literal)
        : value(literal ? "true" : "false") {}

      boolean(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_BOOLEAN_H */

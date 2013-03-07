/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_INTEGER_H
#define XSDXX_INTEGER_H

#include <string> /* for std::to_string() */

#include "xsd++/decimal.h"

namespace xsd {
  class integer : public decimal {
    public:
      static constexpr char name[]    = "integer";
      static constexpr char pattern[] = "^([-+])?0*([0-9]+)$";
      static constexpr bool captures  = 3;

      static bool match(const std::string& literal) noexcept;

      integer(int literal)
        : decimal(std::to_string(literal)) {}

      integer(unsigned int literal)
        : decimal(std::to_string(literal)) {}

      integer(long literal)
        : decimal(std::to_string(literal)) {}

      integer(unsigned long literal)
        : decimal(std::to_string(literal)) {}

      integer(long long literal)
        : decimal(std::to_string(literal)) {}

      integer(unsigned long long literal)
        : decimal(std::to_string(literal)) {}

      integer(const std::string& literal)
        : decimal(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_INTEGER_H */

/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATETIME_H
#define XSDXX_DATETIME_H

#include "xsd++/value.h"

namespace xsd {
  class datetime : public value {
    public:
      static bool match(const std::string& literal) noexcept;

      datetime(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_DATETIME_H */

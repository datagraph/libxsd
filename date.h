/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATE_H
#define XSDXX_DATE_H

#include "xsd++/value.h"

namespace xsd {
  class date : public value {
    public:
      static bool match(const std::string& literal) noexcept;

      date(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_DATE_H */

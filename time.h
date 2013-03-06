/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_TIME_H
#define XSDXX_TIME_H

#include "xsd++/value.h"

namespace xsd {
  class time : public value {
    public:
      static bool match(const std::string& literal) noexcept;

      time(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_TIME_H */

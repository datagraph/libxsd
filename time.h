/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_TIME_H
#define XSDXX_TIME_H

#include "xsd++/value.h"

namespace xsd {
  class time : public value {
    public:
      static constexpr char name[]    = "time";
      static constexpr char pattern[] = "([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$";
      static constexpr bool captures  = 6;

      static bool match(const std::string& literal) noexcept;

      time(const std::string& literal)
        : value(literal) {}

      virtual bool validate() const noexcept override;

      virtual bool canonicalize() noexcept override;
  };
}

#endif /* XSDXX_TIME_H */

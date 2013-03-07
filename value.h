/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_VALUE_H
#define XSDXX_VALUE_H

#include <string> /* for std::string */

namespace xsd {
  class value {
    public:
      bool valid() const noexcept {
        return validate();
      }

      virtual bool validate() const noexcept = 0;

      virtual bool canonicalize() = 0;

      bool operator==(const value& other) const {
        return _literal == other._literal;
      }

      bool operator!=(const value& other) const {
        return _literal != other._literal;
      }

      bool operator<(const value& other) const {
        return _literal < other._literal;
      }

      bool operator<=(const value& other) const {
        return _literal <= other._literal;
      }

      bool operator>(const value& other) const {
        return _literal > other._literal;
      }

      bool operator>=(const value& other) const {
        return _literal >= other._literal;
      }

      virtual operator bool() const;

      virtual operator int() const;

      virtual operator long() const;

      virtual operator long long() const;

      virtual operator double() const;

      virtual operator float() const;

      virtual operator std::string() const;

      const std::string& to_string() const {
        return _literal;
      }

    protected:
      std::string _literal;

      value(const std::string& literal)
        : _literal(literal) {}

      virtual ~value() = default;
  };
}

#endif /* XSDXX_VALUE_H */

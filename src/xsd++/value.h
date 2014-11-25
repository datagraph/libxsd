/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_VALUE_H
#define XSDXX_VALUE_H

#include <string>       /* for std::string */
#include <system_error> /* for std::error_condition */

namespace xsd {
  class value;
}

class xsd::value {
protected:
  std::string _literal;

  value(const std::string& literal)
    : _literal{literal} {}

  value(const char* literal)
    : _literal{literal} {}

  virtual ~value() = default;

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

  virtual explicit operator bool() const;

  virtual explicit operator int() const;

  virtual explicit operator long() const;

  virtual explicit operator long long() const;

  virtual explicit operator double() const;

  virtual explicit operator float() const;

  virtual explicit operator std::string() const;

  const std::string& to_string() const {
    return _literal;
  }

  const char* c_str() const noexcept {
    return _literal.c_str();
  }
};

#endif /* XSDXX_VALUE_H */

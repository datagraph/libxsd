/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_VALUE_H
#define XSDXX_VALUE_H

#include <string>       /* for std::string */
#include <system_error> /* for std::error_condition */

namespace xsd {
  class value;
}

////////////////////////////////////////////////////////////////////////////////

class xsd::value {
protected:
  /**
   * Destructor.
   */
  virtual ~value() = default;

public:
  /**
   * @param literal
   */
  static bool match(const std::string& literal) noexcept;

  /**
   * @copydoc xsd::value::match(std::string&)
   */
  static bool match(const char* literal) noexcept;

  /**
   * ...
   */
  virtual bool normalize() noexcept {
    return false; /* already in normalized form */
  }

  virtual explicit operator bool() const;

  virtual explicit operator int() const;

  virtual explicit operator long() const;

  virtual explicit operator long long() const;

  virtual explicit operator double() const;

  virtual explicit operator float() const;

  virtual explicit operator std::string() const;

  virtual std::string literal() const = 0;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* XSDXX_VALUE_H */

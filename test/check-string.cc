/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/string.h> /* for xsd::string */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE(xsd::string::parse("").value() == "");
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing non-empty literals") {
  GIVEN("a non-empty string") {
    REQUIRE(xsd::string::parse("foobar").value() == "foobar");
  }
}

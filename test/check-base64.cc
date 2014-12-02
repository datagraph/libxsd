/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/base64.h> /* for xsd::base64 */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE(xsd::base64::parse("").value() == "");
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing non-empty literals") {
  GIVEN("a non-empty string") {
    REQUIRE(xsd::base64::parse("Zm9vYmFyCg==").value() == "Zm9vYmFyCg==");
  }
}

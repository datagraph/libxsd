/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/integer.h> /* for xsd::integer */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing zero values") {
  GIVEN("the zero value") {
    REQUIRE(xsd::integer::parse("0").value() == 0);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("negative values") {
  GIVEN("a negative integer") {
    // TODO
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("positive values") {
  GIVEN("a positive integer") {
    // TODO
  }
}

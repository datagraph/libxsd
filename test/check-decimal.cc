/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/decimal.h> /* for xsd::decimal */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::decimal::parse(""), std::invalid_argument);
  }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("test_decimal") {
  // TODO
}

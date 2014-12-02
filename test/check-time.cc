/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/time.h> /* for xsd::time */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::time::parse(""), std::invalid_argument);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals without a timezone") {
  GIVEN("the smallest value") {
    REQUIRE(xsd::time::parse("00:00:00").value() == 0);
  }
  GIVEN("the largest whole value") {
    REQUIRE(xsd::time::parse("23:59:59").value() == 86399*1000000L);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals with a timezone") {
  GIVEN("the smallest value with a Zulu timezone") {
    REQUIRE(xsd::time::parse("00:00:00Z").value() == 0);
    REQUIRE(xsd::time::parse("00:00:00+00:00").value() == 0);
  }
  GIVEN("the smallest value with a non-Zulu timezone") {
    REQUIRE(xsd::time::parse("06:00:00+06:00").value() == 0);
    REQUIRE(xsd::time::parse("18:00:00-06:00").value() == 0);
  }
  GIVEN("the largest whole value with a Zulu timezone") {
    REQUIRE(xsd::time::parse("23:59:59Z").value() == 86399*1000000L);
  }
}

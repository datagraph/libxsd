/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/datetime.h> /* for xsd::datetime */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::datetime::parse(""), std::invalid_argument);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals without a timezone") {
  GIVEN("the epoch value") {
    REQUIRE(xsd::datetime::parse("1970-01-01T00:00:00").value() == 0);
  }
  GIVEN("values before the epoch") {
    REQUIRE(xsd::datetime::parse("1901-12-13T20:45:52").value() == -2147483648000000);  /* -(2^31)  */
  }
  GIVEN("values after the epoch") {
    REQUIRE(xsd::datetime::parse("2038-01-19T03:14:07").value() == 2147483647000000);   /* (2^31)-1 */
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals with a timezone") {
  GIVEN("the epoch value") {
    REQUIRE(xsd::datetime::parse("1970-01-01T00:00:00Z").value() == 0);
  }
  GIVEN("values before the epoch") {
    REQUIRE(xsd::datetime::parse("1901-12-13T20:45:52Z").value() == -2147483648000000); /* -(2^31)  */
  }
  GIVEN("values after the epoch") {
    REQUIRE(xsd::datetime::parse("2038-01-19T03:14:07Z").value() == 2147483647000000);  /* (2^31)-1 */
  }
}

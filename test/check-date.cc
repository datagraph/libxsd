/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/date.h> /* for xsd::date */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing dates without a timezone") {
  GIVEN("the epoch value") {
    REQUIRE(xsd::date::parse("1970-01-01").value() == 0);
  }
  GIVEN("dates before the epoch") {
#ifndef __APPLE__
    REQUIRE(xsd::date::parse("1901-12-13").value() == -2147558400000000);  /* circa -(2^31)  */
#endif
  }
  GIVEN("dates after the epoch") {
    REQUIRE(xsd::date::parse("2038-01-19").value() == 2147472000000000);   /* circa (2^31)-1 */
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing dates with a timezone") {
  GIVEN("the epoch value") {
    REQUIRE(xsd::date::parse("1970-01-01Z").value() == 0);
  }
  GIVEN("dates before the epoch") {
#ifndef __APPLE__
    REQUIRE(xsd::date::parse("1901-12-13Z").value() == -2147558400000000); /* circa -(2^31)  */
#endif
  }
  GIVEN("dates after the epoch") {
    REQUIRE(xsd::date::parse("2038-01-19Z").value() == 2147472000000000);  /* circa (2^31)-1 */
  }
}

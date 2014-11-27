/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/date.h> /* for xsd::date */

TEST_CASE("test_date") {
  REQUIRE(xsd::date::parse("1970-01-01Z") == 0);                 /* epoch          */
  REQUIRE(xsd::date::parse("2038-01-19Z") == 2147472000000000);  /* circa (2^31)-1 */
#ifndef __APPLE__
  REQUIRE(xsd::date::parse("1901-12-13Z") == -2147558400000000); /* circa -(2^31)  */
#endif
}

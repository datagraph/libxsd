/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/datetime.h> /* for xsd::datetime */

TEST_CASE("test_datetime") {
  REQUIRE(xsd::datetime::parse("1970-01-01T00:00:00Z") == 0);                 /* epoch    */
  REQUIRE(xsd::datetime::parse("2038-01-19T03:14:07Z") == 2147483647000000);  /* (2^31)-1 */
  REQUIRE(xsd::datetime::parse("1901-12-13T20:45:52Z") == -2147483648000000); /* -(2^31)  */
}

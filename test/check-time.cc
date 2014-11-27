/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/time.h> /* for xsd::time */

TEST_CASE("without_tz") {
  REQUIRE(xsd::time::parse("00:00:00") == 0);
}

TEST_CASE("with_tz") {
  REQUIRE(xsd::time::parse("00:00:00Z") == 0);
}

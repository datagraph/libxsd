/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/double.h> /* for xsd::double */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::double_::parse(""), std::invalid_argument);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("negative values") {
  GIVEN("negative zero") {
    // TODO
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("positive values") {
  GIVEN("positive zero") {
    // TODO
  }
}

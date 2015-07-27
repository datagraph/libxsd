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

SCENARIO("parsing literals representing special values") {
  GIVEN("positive zero (0.0)") {
    const auto value = xsd::decimal::parse("0.0").value();
    REQUIRE(value.integer == 0);
    REQUIRE(value.scale   == 0);
  }
  GIVEN("positive zero (+0.0)") {
    const auto value = xsd::decimal::parse("+0.0").value();
    REQUIRE(value.integer == 0);
    REQUIRE(value.scale   == 0);
  }
  GIVEN("negative zero (-0.0)") {
    const auto value = xsd::decimal::parse("-0.0").value();
    REQUIRE(value.integer == 0);
    REQUIRE(value.scale   == 0);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals with leading zeroes in the scale") {
  GIVEN("1.0") {
    const auto value = xsd::decimal::parse("1.0").value();
    REQUIRE(value.integer == 1);
    REQUIRE(value.scale   == 0);
  }
  GIVEN("1.2") {
    const auto value = xsd::decimal::parse("1.2").value();
    REQUIRE(value.integer == 12);
    REQUIRE(value.scale   == 1);
  }
  GIVEN("1.02") {
    const auto value = xsd::decimal::parse("1.02").value();
    REQUIRE(value.integer == 102);
    REQUIRE(value.scale   == 2);
  }
  GIVEN("1.002") {
    const auto value = xsd::decimal::parse("1.002").value();
    REQUIRE(value.integer == 1002);
    REQUIRE(value.scale   == 3);
  }
}

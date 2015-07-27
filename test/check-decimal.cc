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

SCENARIO("parsing literals having only fractional digits") {
  GIVEN("0.1") {
    const auto value = xsd::decimal::parse("0.1").value();
    REQUIRE(value.integer == 1);
    REQUIRE(value.scale   == 1);
  }
  GIVEN("0.01") {
    const auto value = xsd::decimal::parse("0.01").value();
    REQUIRE(value.integer == 1);
    REQUIRE(value.scale   == 2);
  }
  GIVEN("0.001") {
    const auto value = xsd::decimal::parse("0.001").value();
    REQUIRE(value.integer == 1);
    REQUIRE(value.scale   == 3);
  }
  GIVEN("0.0001") {
    const auto value = xsd::decimal::parse("0.0001").value();
    REQUIRE(value.integer == 1);
    REQUIRE(value.scale   == 4);
  }
}

SCENARIO("parsing literals having leading zeroes in the fraction") {
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

////////////////////////////////////////////////////////////////////////////////

SCENARIO("decimal comparisons") {
  GIVEN("0.0 <=> 0.0") {
    const xsd::decimal decimal1{{0, 0}}, decimal2{{0, 0}};
    REQUIRE(decimal1.compare(decimal2) == 0);
    REQUIRE(decimal2.compare(decimal1) == 0);
  }
  GIVEN("0.0 <=> 1.0") {
    const xsd::decimal decimal1{{0, 0}}, decimal2{{1, 0}};
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
  GIVEN("0.1 <=> 1.0") {
    const xsd::decimal decimal1{{1, 1}}, decimal2{{1, 0}};
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
  GIVEN("0.1 <=> 0.22") {
    const xsd::decimal decimal1{{1, 1}}, decimal2{{22, 2}};
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
}

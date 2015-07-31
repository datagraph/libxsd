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
    REQUIRE(value.digits  == 0);
    REQUIRE(value.scale   == 0);
    REQUIRE(value.sign    == true);
  }
  GIVEN("positive zero (+0.0)") {
    const auto value = xsd::decimal::parse("+0.0").value();
    REQUIRE(value.digits  == 0);
    REQUIRE(value.scale   == 0);
    REQUIRE(value.sign    == true);
  }
  GIVEN("negative zero (-0.0)") {
    const auto value = xsd::decimal::parse("-0.0").value();
    REQUIRE(value.digits  == 0);
    REQUIRE(value.scale   == 0);
    REQUIRE(value.sign    == true); // FIXME
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals having only fractional digits") {
  GIVEN("0.1") {
    const auto value = xsd::decimal::parse("0.1").value();
    REQUIRE(value.digits  == 1);
    REQUIRE(value.scale   == 1);
    REQUIRE(value.sign    == true);
  }
  GIVEN("0.01") {
    const auto value = xsd::decimal::parse("0.01").value();
    REQUIRE(value.digits  == 1);
    REQUIRE(value.scale   == 2);
    REQUIRE(value.sign    == true);
  }
  GIVEN("0.001") {
    const auto value = xsd::decimal::parse("0.001").value();
    REQUIRE(value.digits  == 1);
    REQUIRE(value.scale   == 3);
    REQUIRE(value.sign    == true);
  }
  GIVEN("0.0001") {
    const auto value = xsd::decimal::parse("0.0001").value();
    REQUIRE(value.digits  == 1);
    REQUIRE(value.scale   == 4);
    REQUIRE(value.sign    == true);
  }
}

SCENARIO("parsing literals having leading zeroes in the fraction") {
  GIVEN("1.0") {
    const auto value = xsd::decimal::parse("1.0").value();
    REQUIRE(value.digits  == 1);
    REQUIRE(value.scale   == 0);
    REQUIRE(value.sign    == true);
  }
  GIVEN("1.2") {
    const auto value = xsd::decimal::parse("1.2").value();
    REQUIRE(value.digits  == 12);
    REQUIRE(value.scale   == 1);
    REQUIRE(value.sign    == true);
  }
  GIVEN("1.02") {
    const auto value = xsd::decimal::parse("1.02").value();
    REQUIRE(value.digits  == 102);
    REQUIRE(value.scale   == 2);
    REQUIRE(value.sign    == true);
  }
  GIVEN("1.002") {
    const auto value = xsd::decimal::parse("1.002").value();
    REQUIRE(value.digits  == 1002);
    REQUIRE(value.scale   == 3);
    REQUIRE(value.sign    == true);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("comparisons of special values") {
  GIVEN("0.0 <=> 0.0") {
    const xsd::decimal decimal1{{0, 0, true}}, decimal2{{0, 0, true}};
    REQUIRE(decimal1.compare(decimal2) == 0);
    REQUIRE(decimal2.compare(decimal1) == 0);
  }
}

SCENARIO("comparisons of negative/nonnegative values") {
  GIVEN("-1.0 <=> -1.0") {
    const auto negative1 = xsd::decimal::parse("-1.0");
    const auto negative2 = xsd::decimal::parse("-1.0");
    REQUIRE(negative1.compare(negative2) == 0);
    REQUIRE(negative2.compare(negative1) == 0);
  }
  GIVEN("-1.0 <=> +0.0") {
    const auto negative = xsd::decimal::parse("-1.0");
    const auto positive = xsd::decimal::parse("+0.0");
    REQUIRE(negative.compare(positive) == -1);
    REQUIRE(positive.compare(negative) == 1);
  }
  GIVEN("-1.0 <=> +1.0") {
    const auto negative = xsd::decimal::parse("-1.0");
    const auto positive = xsd::decimal::parse("+1.0");
    REQUIRE(negative.compare(positive) == -1);
    REQUIRE(positive.compare(negative) == 1);
  }
  GIVEN("-0.1 <=> +0.1") {
    const auto negative = xsd::decimal::parse("-0.1");
    const auto positive = xsd::decimal::parse("+0.1");
    REQUIRE(negative.compare(positive) == -1);
    REQUIRE(positive.compare(negative) == 1);
  }
}

SCENARIO("comparisons of fractional values") {
  GIVEN("0.0 <=> 1.0") {
    const auto decimal1 = xsd::decimal::parse("0.0");
    const auto decimal2 = xsd::decimal::parse("1.0");
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
  GIVEN("0.1 <=> 1.0") {
    const auto decimal1 = xsd::decimal::parse("0.1");
    const auto decimal2 = xsd::decimal::parse("1.0");
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
  GIVEN("0.1 <=> 0.22") {
    const auto decimal1 = xsd::decimal::parse("0.1");
    const auto decimal2 = xsd::decimal::parse("0.22");
    REQUIRE(decimal1.compare(decimal2) == -1);
    REQUIRE(decimal2.compare(decimal1) == 1);
  }
}

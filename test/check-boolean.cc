/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/boolean.h> /* for xsd::boolean */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::boolean::parse(""), std::invalid_argument);
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

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("match_empty") {
  REQUIRE(!xsd::boolean::match(""));
}

TEST_CASE("match_false") {
  REQUIRE(xsd::boolean::match("false"));
}

TEST_CASE("match_true") {
  REQUIRE(xsd::boolean::match("true"));
}

TEST_CASE("match_0") {
  REQUIRE(xsd::boolean::match("0"));
}

TEST_CASE("match_1") {
  REQUIRE(xsd::boolean::match("1"));
}

TEST_CASE("construct_from_value") {
  REQUIRE(xsd::boolean(false).literal() == "false");
  REQUIRE(xsd::boolean(true).literal() == "true");
}

TEST_CASE("validate") {
  REQUIRE(xsd::boolean::validate("false"));
  REQUIRE(xsd::boolean::validate("true"));
  REQUIRE(xsd::boolean::validate("0"));
  REQUIRE(xsd::boolean::validate("1"));
}

TEST_CASE("canonicalize_false") {
  std::string literal{"false"};
  REQUIRE(xsd::boolean::canonicalize(literal) == false);
}

TEST_CASE("canonicalize_true") {
  std::string literal{"true"};
  REQUIRE(xsd::boolean::canonicalize(literal) == false);
}

TEST_CASE("canonicalize_0") {
  std::string literal{"0"};
  REQUIRE(xsd::boolean::canonicalize(literal) == true);
  REQUIRE(literal == "false");
}

TEST_CASE("canonicalize_1") {
  std::string literal{"1"};
  REQUIRE(xsd::boolean::canonicalize(literal) == true);
  REQUIRE(literal == "true");
}

TEST_CASE("canonicalize_invalid") {
  std::string literal{""};
  REQUIRE_THROWS_AS(xsd::boolean::canonicalize(literal), std::invalid_argument);
}

TEST_CASE("cast_to_bool") {
  REQUIRE((bool)xsd::boolean(false) == false);
  REQUIRE((bool)xsd::boolean(true) == true);
}

#if 0
TEST_CASE("cast_to_int") {
  REQUIRE_THROWS_AS((int)xsd::boolean(false), std::bad_cast);
  REQUIRE_THROWS_AS((int)xsd::boolean(true), std::bad_cast);
}

TEST_CASE("cast_to_long") {
  REQUIRE_THROWS_AS((long)xsd::boolean(false), std::bad_cast);
  REQUIRE_THROWS_AS((long)xsd::boolean(true), std::bad_cast);
}

TEST_CASE("cast_to_long_long") {
  REQUIRE_THROWS_AS((long long)xsd::boolean(false), std::bad_cast);
  REQUIRE_THROWS_AS((long long)xsd::boolean(true), std::bad_cast);
}

TEST_CASE("cast_to_double") {
  REQUIRE_THROWS_AS((double)xsd::boolean(false), std::bad_cast);
  REQUIRE_THROWS_AS((double)xsd::boolean(true), std::bad_cast);
}

TEST_CASE("cast_to_float") {
  REQUIRE_THROWS_AS((float)xsd::boolean(false), std::bad_cast);
  REQUIRE_THROWS_AS((float)xsd::boolean(true), std::bad_cast);
}

TEST_CASE("cast_literal") {
  REQUIRE((std::string)xsd::boolean(false) == "false");
  REQUIRE((std::string)xsd::boolean(true) == "true");
  REQUIRE((std::string)xsd::boolean("false") == "false");
  REQUIRE((std::string)xsd::boolean("true") == "true");
  REQUIRE((std::string)xsd::boolean("0") == "0");
  REQUIRE((std::string)xsd::boolean("1") == "1");
}
#endif

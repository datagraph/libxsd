/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/boolean.h> /* for xsd::boolean */

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
  REQUIRE(xsd::boolean(false).to_string() == "false");
  REQUIRE(xsd::boolean(true).to_string() == "true");
}

TEST_CASE("construct_from_string") {
  REQUIRE(xsd::boolean("false").to_string() == "false");
  REQUIRE(xsd::boolean("true").to_string() == "true");
  REQUIRE(xsd::boolean("0").to_string() == "0");
  REQUIRE(xsd::boolean("1").to_string() == "1");
}

TEST_CASE("validate") {
  REQUIRE(xsd::boolean("false").validate());
  REQUIRE(xsd::boolean("true").validate());
  REQUIRE(xsd::boolean("0").validate());
  REQUIRE(xsd::boolean("1").validate());
}

TEST_CASE("canonicalize_false") {
  xsd::boolean value("false");
  REQUIRE(value.canonicalize() == false);
  REQUIRE(value.to_string() == "false");
}

TEST_CASE("canonicalize_true") {
  xsd::boolean value("true");
  REQUIRE(value.canonicalize() == false);
  REQUIRE(value.to_string() == "true");
}

TEST_CASE("canonicalize_0") {
  xsd::boolean value("0");
  REQUIRE(value.canonicalize() == true);
  REQUIRE(value.to_string() == "false");
}

TEST_CASE("canonicalize_1") {
  xsd::boolean value("1");
  REQUIRE(value.canonicalize() == true);
  REQUIRE(value.to_string() == "true");
}

TEST_CASE("canonicalize_invalid") {
  xsd::boolean value("");
  REQUIRE_THROWS_AS(value.canonicalize(), std::invalid_argument);
}

TEST_CASE("cast_to_bool") {
  REQUIRE((bool)xsd::boolean(false) == false);
  REQUIRE((bool)xsd::boolean(true) == true);
  REQUIRE((bool)xsd::boolean("false") == false);
  REQUIRE((bool)xsd::boolean("true") == true);
  REQUIRE((bool)xsd::boolean("0") == false);
  REQUIRE((bool)xsd::boolean("1") == true);
  REQUIRE_THROWS_AS((bool)xsd::boolean(""), std::bad_cast);
}

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

TEST_CASE("cast_to_string") {
  REQUIRE((std::string)xsd::boolean(false) == "false");
  REQUIRE((std::string)xsd::boolean(true) == "true");
  REQUIRE((std::string)xsd::boolean("false") == "false");
  REQUIRE((std::string)xsd::boolean("true") == "true");
  REQUIRE((std::string)xsd::boolean("0") == "0");
  REQUIRE((std::string)xsd::boolean("1") == "1");
}

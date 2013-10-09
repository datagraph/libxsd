/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE boolean
#include <boost/test/unit_test.hpp>

#include <xsd++/boolean.h> /* for xsd::boolean */

BOOST_AUTO_TEST_CASE(match_empty) {
  BOOST_CHECK(!xsd::boolean::match(""));
}

BOOST_AUTO_TEST_CASE(match_false) {
  BOOST_CHECK(xsd::boolean::match("false"));
}

BOOST_AUTO_TEST_CASE(match_true) {
  BOOST_CHECK(xsd::boolean::match("true"));
}

BOOST_AUTO_TEST_CASE(match_0) {
  BOOST_CHECK(xsd::boolean::match("0"));
}

BOOST_AUTO_TEST_CASE(match_1) {
  BOOST_CHECK(xsd::boolean::match("1"));
}

BOOST_AUTO_TEST_CASE(construct_from_value) {
  BOOST_CHECK_EQUAL(xsd::boolean(false).to_string(), "false");
  BOOST_CHECK_EQUAL(xsd::boolean(true).to_string(), "true");
}

BOOST_AUTO_TEST_CASE(construct_from_string) {
  BOOST_CHECK_EQUAL(xsd::boolean("false").to_string(), "false");
  BOOST_CHECK_EQUAL(xsd::boolean("true").to_string(), "true");
  BOOST_CHECK_EQUAL(xsd::boolean("0").to_string(), "0");
  BOOST_CHECK_EQUAL(xsd::boolean("1").to_string(), "1");
}

BOOST_AUTO_TEST_CASE(validate) {
  BOOST_CHECK(xsd::boolean("false").validate());
  BOOST_CHECK(xsd::boolean("true").validate());
  BOOST_CHECK(xsd::boolean("0").validate());
  BOOST_CHECK(xsd::boolean("1").validate());
}

BOOST_AUTO_TEST_CASE(canonicalize_false) {
  xsd::boolean value("false");
  BOOST_CHECK_EQUAL(value.canonicalize(), false);
  BOOST_CHECK_EQUAL(value.to_string(), "false");
}

BOOST_AUTO_TEST_CASE(canonicalize_true) {
  xsd::boolean value("true");
  BOOST_CHECK_EQUAL(value.canonicalize(), false);
  BOOST_CHECK_EQUAL(value.to_string(), "true");
}

BOOST_AUTO_TEST_CASE(canonicalize_0) {
  xsd::boolean value("0");
  BOOST_CHECK_EQUAL(value.canonicalize(), true);
  BOOST_CHECK_EQUAL(value.to_string(), "false");
}

BOOST_AUTO_TEST_CASE(canonicalize_1) {
  xsd::boolean value("1");
  BOOST_CHECK_EQUAL(value.canonicalize(), true);
  BOOST_CHECK_EQUAL(value.to_string(), "true");
}

BOOST_AUTO_TEST_CASE(canonicalize_invalid) {
  xsd::boolean value("");
  BOOST_CHECK_EQUAL(value.canonicalize(), false);
}

BOOST_AUTO_TEST_CASE(cast_to_bool) {
  BOOST_CHECK_EQUAL((bool)xsd::boolean(false), false);
  BOOST_CHECK_EQUAL((bool)xsd::boolean(true), true);
  BOOST_CHECK_EQUAL((bool)xsd::boolean("false"), false);
  BOOST_CHECK_EQUAL((bool)xsd::boolean("true"), true);
  BOOST_CHECK_EQUAL((bool)xsd::boolean("0"), false);
  BOOST_CHECK_EQUAL((bool)xsd::boolean("1"), true);
  BOOST_CHECK_THROW((bool)xsd::boolean(""), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_int) {
  BOOST_CHECK_THROW((int)xsd::boolean(false), std::bad_cast);
  BOOST_CHECK_THROW((int)xsd::boolean(true), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_long) {
  BOOST_CHECK_THROW((long)xsd::boolean(false), std::bad_cast);
  BOOST_CHECK_THROW((long)xsd::boolean(true), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_long_long) {
  BOOST_CHECK_THROW((long long)xsd::boolean(false), std::bad_cast);
  BOOST_CHECK_THROW((long long)xsd::boolean(true), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_double) {
  BOOST_CHECK_THROW((double)xsd::boolean(false), std::bad_cast);
  BOOST_CHECK_THROW((double)xsd::boolean(true), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_float) {
  BOOST_CHECK_THROW((float)xsd::boolean(false), std::bad_cast);
  BOOST_CHECK_THROW((float)xsd::boolean(true), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(cast_to_string) {
  BOOST_CHECK_EQUAL((std::string)xsd::boolean(false), "false");
  BOOST_CHECK_EQUAL((std::string)xsd::boolean(true), "true");
  BOOST_CHECK_EQUAL((std::string)xsd::boolean("false"), "false");
  BOOST_CHECK_EQUAL((std::string)xsd::boolean("true"), "true");
  BOOST_CHECK_EQUAL((std::string)xsd::boolean("0"), "0");
  BOOST_CHECK_EQUAL((std::string)xsd::boolean("1"), "1");
}

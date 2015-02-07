/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/extern.h> /* for xsd_*_*() */

#include <cerrno>         /* for E*, errno */
#include <cmath>          /* for std::isinf(), std::isnan() */

////////////////////////////////////////////////////////////////////////////////
/* xsd:base64Binary */

TEST_CASE("xsd_base64_validate()") {
  //REQUIRE(xsd_base64_validate("") == false); // FIXME
  // TODO
}

TEST_CASE("xsd_base64_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_base64_value()") {
  errno = 0;
  //REQUIRE(std::strcmp(xsd_base64_value(""), "") == 0); // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:boolean */

TEST_CASE("xsd_boolean_validate()") {
  REQUIRE(xsd_boolean_validate("") == false);
  REQUIRE(xsd_boolean_validate("true") == true);
  REQUIRE(xsd_boolean_validate("false") == true);
  REQUIRE(xsd_boolean_validate("1") == true);
  REQUIRE(xsd_boolean_validate("0") == true);
  // TODO
}

TEST_CASE("xsd_boolean_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_boolean_value()") {
  errno = 0;
  REQUIRE(xsd_boolean_value("true") == true);
  REQUIRE(xsd_boolean_value("false") == false);
  REQUIRE(xsd_boolean_value("1") == true);
  REQUIRE(xsd_boolean_value("0") == false);
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:date */

TEST_CASE("xsd_date_validate()") {
  REQUIRE(xsd_date_validate("") == false);
  REQUIRE(xsd_date_validate("1970-01-01") == true);
  // TODO
}

TEST_CASE("xsd_date_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_date_value()") {
  errno = 0;
  REQUIRE(xsd_date_value("1970-01-01") == 0);
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:dateTime */

TEST_CASE("xsd_datetime_validate()") {
  REQUIRE(xsd_datetime_validate("") == false);
  REQUIRE(xsd_datetime_validate("1970-01-01T00:00:00") == true);
  // TODO
}

TEST_CASE("xsd_datetime_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_datetime_value()") {
  errno = 0;
  REQUIRE(xsd_datetime_value("1970-01-01T00:00:00") == 0);
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:decimal */

TEST_CASE("xsd_decimal_validate()") {
  REQUIRE(xsd_decimal_validate("") == false);
  REQUIRE(xsd_decimal_validate("0") == true);
  REQUIRE(xsd_decimal_validate("0.0") == true);
  // TODO
}

TEST_CASE("xsd_decimal_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_decimal_value()") {
  errno = 0;
  REQUIRE(xsd_decimal_value("0") == 0.0);
  //REQUIRE(xsd_decimal_value("0.5") == 0.5); // FIXME
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:double */

TEST_CASE("xsd_double_validate()") {
  REQUIRE(xsd_double_validate("") == false);
  REQUIRE(xsd_double_validate("0") == true);
  REQUIRE(xsd_double_validate("0.0") == true);
  // TODO
}

TEST_CASE("xsd_double_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_double_value()") {
  errno = 0;
  REQUIRE(xsd_double_value("3.1415") == 3.1415);
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:duration */

TEST_CASE("xsd_duration_validate()") {
  REQUIRE(xsd_duration_validate("") == false);
  // TODO
}

TEST_CASE("xsd_duration_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_duration_value()") {
  errno = 0;
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:float */

TEST_CASE("xsd_float_validate()") {
  REQUIRE(xsd_float_validate("") == false);
  REQUIRE(xsd_float_validate("0") == true);
  REQUIRE(xsd_float_validate("0.0") == true);
  // TODO
}

TEST_CASE("xsd_float_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_float_value()") {
  errno = 0;
  REQUIRE(xsd_float_value("3.1415") == 3.1415f);
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:integer */

TEST_CASE("xsd_integer_validate()") {
  REQUIRE(xsd_integer_validate("") == false);
  REQUIRE(xsd_integer_validate("0") == true);
  REQUIRE(xsd_integer_validate("0.0") == false);
  // TODO
}

TEST_CASE("xsd_integer_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_integer_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_int8_value()") {
  errno = 0;
  REQUIRE(xsd_int8_value("-129") == INT8_MIN);
  REQUIRE(xsd_int8_value("-128") == -128);
  REQUIRE(xsd_int8_value("0") == 0);
  REQUIRE(xsd_int8_value("127") == 127);
  REQUIRE(xsd_int8_value("128") == INT8_MAX);
}

TEST_CASE("xsd_int16_value()") {
  errno = 0;
  REQUIRE(xsd_int16_value("-32769") == INT16_MIN);
  REQUIRE(xsd_int16_value("-32768") == -32768);
  REQUIRE(xsd_int16_value("0") == 0);
  REQUIRE(xsd_int16_value("32767") == 32767);
  REQUIRE(xsd_int16_value("32768") == INT16_MAX);
}

TEST_CASE("xsd_int32_value()") {
  errno = 0;
  REQUIRE(xsd_int32_value("-2147483649") == INT32_MIN);
  REQUIRE(xsd_int32_value("-2147483648") == -2147483648);
  REQUIRE(xsd_int32_value("0") == 0);
  REQUIRE(xsd_int32_value("2147483647") == 2147483647);
  REQUIRE(xsd_int32_value("2147483648") == INT32_MAX);
}

TEST_CASE("xsd_int64_value()") {
  errno = 0;
  //REQUIRE(xsd_int64_value("-9223372036854775809") == INT64_MIN); // FIXME
  //REQUIRE(xsd_int64_value("-9223372036854775808") == -9223372036854775807LL-1); // FIXME
  REQUIRE(xsd_int64_value("0") == 0);
  REQUIRE(xsd_int64_value("9223372036854775807") == 9223372036854775807LL);
  REQUIRE(xsd_int64_value("9223372036854775808") == INT64_MAX);
}

TEST_CASE("xsd_intmax_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_uint8_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_uint16_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_uint32_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_uint64_value()") {
  errno = 0;
  // TODO
}

TEST_CASE("xsd_uintmax_value()") {
  errno = 0;
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:string */

TEST_CASE("xsd_string_validate()") {
  REQUIRE(xsd_string_validate("") == true);
  REQUIRE(xsd_string_validate("foobar") == true);
}

TEST_CASE("xsd_string_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_string_value()") {
  errno = 0;
  REQUIRE(std::strcmp(xsd_string_value(""), "") == 0);
  REQUIRE(std::strcmp(xsd_string_value(""), " ") != 0);
  REQUIRE(std::strcmp(xsd_string_value("foobar"), "foobar") == 0);
  REQUIRE(std::strcmp(xsd_string_value("foobar"), "FOOBAR") != 0);
}

////////////////////////////////////////////////////////////////////////////////
/* xsd:time */

TEST_CASE("xsd_time_validate()") {
  REQUIRE(xsd_time_validate("") == false);
  REQUIRE(xsd_time_validate("00:00:00") == true);
  // TODO
}

TEST_CASE("xsd_time_canonicalize()") {
  // TODO
}

TEST_CASE("xsd_time_value()") {
  errno = 0;
  SECTION("parsing invalid literals") {
    REQUIRE(xsd_time_value("T00:00:00") == 0);
    REQUIRE(errno == EINVAL);
  }
  SECTION("parsing literals without a timezone") {
    SECTION("the smallest value") {
      REQUIRE(xsd_time_value("00:00:00") == 0);
    }
    SECTION("the largest whole value") {
      REQUIRE(xsd_time_value("23:59:59") == 86399*1000000L);
    }
  }
  SECTION("parsing literals with a timezone") {
    SECTION("the smallest value with a Zulu timezone") {
      REQUIRE(xsd_time_value("00:00:00Z") == 0);
      REQUIRE(xsd_time_value("00:00:00+00:00") == 0);
    }
    SECTION("the smallest value with a non-Zulu timezone") {
      REQUIRE(xsd_time_value("06:00:00+06:00") == 0);
      REQUIRE(xsd_time_value("18:00:00-06:00") == 0);
    }
    SECTION("the largest whole value with a Zulu timezone") {
      REQUIRE(xsd_time_value("23:59:59Z") == 86399*1000000L);
    }
  }
}

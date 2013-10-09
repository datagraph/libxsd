AM_CPPFLAGS += $(TEST_CPPFLAGS)
AM_CXXFLAGS += $(TEST_CXXFLAGS)
AM_LDFLAGS  += $(TEST_LDFLAGS)

LDADD = $(top_srcdir)/src/xsd++/libxsd++.la

check_PROGRAMS = \
  check_base64   \
  check_boolean  \
  check_date     \
  check_datetime \
  check_decimal  \
  check_double   \
  check_feature  \
  check_float    \
  check_integer  \
  check_module   \
  check_string   \
  check_time     \
  check_version

TESTS = $(check_PROGRAMS)

AM_DEFAULT_SOURCE_EXT = .cc

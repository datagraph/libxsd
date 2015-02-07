AM_CPPFLAGS += $(TEST_CPPFLAGS)
AM_CXXFLAGS += $(TEST_CXXFLAGS)
AM_LDFLAGS  += $(TEST_LDFLAGS)

LDADD = $(top_srcdir)/src/xsd++/libxsd++.la

check_PROGRAMS = \
  check-base64   \
  check-boolean  \
  check-date     \
  check-datetime \
  check-decimal  \
  check-double   \
  check-duration \
  check-extern   \
  check-feature  \
  check-float    \
  check-integer  \
  check-module   \
  check-string   \
  check-time     \
  check-version

TESTS = $(check_PROGRAMS)

AM_DEFAULT_SOURCE_EXT = .cc

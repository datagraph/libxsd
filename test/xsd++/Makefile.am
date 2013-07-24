AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src -iquote $(srcdir) $(BOOST_CPPFLAGS) -DBOOST_TEST_DYN_LINK
AM_CXXFLAGS = -Wall -Wextra -pipe
AM_LDFLAGS  = $(BOOST_LDFLAGS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
LDADD       = $(top_srcdir)/src/xsd++/libxsd++.la

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

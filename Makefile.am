AM_CPPFLAGS     = -I$(top_srcdir)/lib -I$(top_srcdir)/src -iquote $(srcdir)
AM_CXXFLAGS     = -Wall -Wextra -pipe
AM_LDFLAGS      = -rdynamic -Xlinker '-z,relro' -Xlinker '--as-needed'
LDADD           = libxsd++.la
lib_LTLIBRARIES = libxsd++.la

libxsd___la_SOURCES =     \
  base64.cc               \
  boolean.cc              \
  date.cc                 \
  datetime.cc             \
  decimal.cc              \
  double.cc               \
  extern.cc               \
  feature.cc              \
  float.cc                \
  integer.cc              \
  module.cc               \
  string.cc               \
  time.cc                 \
  value.cc                \
  version.cc

base_pkgincludedir = $(includedir)/xsd++

base_pkginclude_HEADERS = \
  base64.h                \
  boolean.h               \
  date.h                  \
  datetime.h              \
  decimal.h               \
  double.h                \
  extern.h                \
  feature.h               \
  float.h                 \
  integer.h               \
  module.h                \
  string.h                \
  time.h                  \
  value.h                 \
  version.h

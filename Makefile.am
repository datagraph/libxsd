AM_CPPFLAGS     = -I$(top_srcdir)/lib -I$(top_srcdir)/src -iquote $(srcdir)
AM_CXXFLAGS     = -Wall -Wextra -pipe
AM_LDFLAGS      = -rdynamic -Xlinker '-z,relro' -Xlinker '--as-needed'
LDADD           = libxsd++.la
lib_LTLIBRARIES = libxsd++.la

libxsd___la_SOURCES =     \
  feature.cc              \
  module.cc               \
  version.cc

base_pkgincludedir = $(includedir)/xsd++

base_pkginclude_HEADERS = \
  feature.h               \
  module.h                \
  version.h

/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_REGEX_H
#define XSDXX_REGEX_H

/**
 * This is a workaround for missing C++11 <regex> support in libstdc++.
 *
 * @see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=53631
 */

#include <boost/config.hpp>

#ifdef BOOST_GNU_STDLIB /* libstdc++ */

#include <boost/regex.hpp>

namespace std {
  using ::boost::cmatch;
  using ::boost::csub_match;
  using ::boost::regex;
  using ::boost::regex_match;
  namespace regex_constants {
    using namespace ::boost::regex_constants;
  }
}

#else /* !BOOST_GNU_STDLIB */

#include <regex> /* for std::cmatch, std::regex*, std::regex_match() */

#endif /* !BOOST_GNU_STDLIB */

#endif /* XSDXX_REGEX_H */

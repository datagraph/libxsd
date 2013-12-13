/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_H
#define XSDXX_H

/**
 * libxsd++
 */

namespace xsd {
  static constexpr char base_uri[] = "http://www.w3.org/2001/XMLSchema#";
  static constexpr unsigned int base_uri_length = sizeof(base_uri);
}

#include "xsd++/base64.h"
#include "xsd++/boolean.h"
#include "xsd++/const.h"
#include "xsd++/date.h"
#include "xsd++/datetime.h"
#include "xsd++/decimal.h"
#include "xsd++/double.h"
#include "xsd++/feature.h"
#include "xsd++/float.h"
#include "xsd++/integer.h"
#include "xsd++/module.h"
#include "xsd++/string.h"
#include "xsd++/time.h"
#include "xsd++/value.h"
#include "xsd++/version.h"

#endif /* XSDXX_H */

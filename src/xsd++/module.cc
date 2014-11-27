/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "module.h"

////////////////////////////////////////////////////////////////////////////////

static const char* const module_names[] = {
  "base64",
  "boolean",
  "date",
  "datetime",
  "decimal",
  "double",
  "duration",
  "float",
  "integer",
  "string",
  "time",
  nullptr
};

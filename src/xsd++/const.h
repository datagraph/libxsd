/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_CONST_H
#define XSDXX_CONST_H

#define XSD_STRING              "string"
#define XSD_TOKEN               "token"
#define XSD_BOOLEAN             "boolean"
#define XSD_DECIMAL             "decimal"
#define XSD_INTEGER             "integer"
#define XSD_LONG                "long"
#define XSD_ULONG               "unsignedLong"
#define XSD_INT                 "int"
#define XSD_UINT                "unsignedInt"
#define XSD_SHORT               "short"
#define XSD_USHORT              "unsignedShort"
#define XSD_BYTE                "byte"
#define XSD_UBYTE               "unsignedByte"
#define XSD_FLOAT               "float"
#define XSD_DOUBLE              "double"
#define XSD_TIME                "time"
#define XSD_DATE                "date"
#define XSD_DATETIME            "dateTime"
#define XSD_DURATION            "duration"

#define XSD_BASE_URI            "http://www.w3.org/2001/XMLSchema#"
#define XSD_BASE_LEN            (sizeof(XSD_BASE_URI) - 1)

#define XSD_STRING_URI          XSD_BASE_URI XSD_STRING
#define XSD_TOKEN_URI           XSD_BASE_URI XSD_TOKEN
#define XSD_BOOLEAN_URI         XSD_BASE_URI XSD_BOOLEAN
#define XSD_DECIMAL_URI         XSD_BASE_URI XSD_DECIMAL
#define XSD_INTEGER_URI         XSD_BASE_URI XSD_INTEGER
#define XSD_LONG_URI            XSD_BASE_URI XSD_LONG
#define XSD_ULONG_URI           XSD_BASE_URI XSD_ULONG
#define XSD_INT_URI             XSD_BASE_URI XSD_INT
#define XSD_UINT_URI            XSD_BASE_URI XSD_UINT
#define XSD_SHORT_URI           XSD_BASE_URI XSD_SHORT
#define XSD_USHORT_URI          XSD_BASE_URI XSD_USHORT
#define XSD_BYTE_URI            XSD_BASE_URI XSD_BYTE
#define XSD_UBYTE_URI           XSD_BASE_URI XSD_UBYTE
#define XSD_DOUBLE_URI          XSD_BASE_URI XSD_DOUBLE
#define XSD_FLOAT_URI           XSD_BASE_URI XSD_FLOAT
#define XSD_TIME_URI            XSD_BASE_URI XSD_TIME
#define XSD_DATE_URI            XSD_BASE_URI XSD_DATE
#define XSD_DATETIME_URI        XSD_BASE_URI XSD_DATETIME
#define XSD_DURATION_URI        XSD_BASE_URI XSD_DURATION

/* regular expressions from:
   W3C XML Schema Definition Language (XSD) 1.1 Part 2: Datatypes
   W3C Recommendation 5 April 2012
   decimal: (\+|-)?([0-9]+(\.[0-9]*)?|\.[0-9]+)
   float:   (\+|-)?([0-9]+(\.[0-9]*)?|\.[0-9]+)([Ee](\+|-)?[0-9]+)?|(\+|-)?INF|NaN
   decimal: identical to float
*/

#define XSD_STRING_PATTERN      "^(.*)$" // 1 group -> 2 captures
#define XSD_BOOLEAN_PATTERN     "^(true|false|1|0)$" // 1 group -> 2 captures
//#define XSD_DECIMAL_PATTERN   "^([-+])?0*([0-9]*)\\.?(0*[1-9]*)0*$" // 3 groups -> 4 captures
#define XSD_DECIMAL_PATTERN     "^([-+])?0*([0-9]*)(?:\\.([0-9]*)0*)?$" // 3 groups -> 4 captures
#define XSD_INTEGER_PATTERN     "^([-+])?0*([0-9]+)$" // 2 groups -> 3 captures
//#define XSD_FLOAT_PATTERN     "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$" // 5  groups -> 6 captures
#define XSD_FLOAT_PATTERN       "^([-+])?0*([0-9]*)(?:\\.([0-9]*)0*)?(?:[Ee]([-+])?0*([0-9]+)0*)?$" // 5  groups -> 6 captures
#define XSD_DOUBLE_PATTERN      XSD_FLOAT_PATTERN
#define XSD_TIME_PATTERN        "([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$" // 6 groups -> 7 captures
#define XSD_DATE_PATTERN        "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})(Z|([-+][0-9]{2}:[0-9]{2}))?$" // 6 groups -> 7 captures
#define XSD_DATETIME_PATTERN    "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$" // 10 groups -> 11 captures
#define XSD_DURATION_PATTERN    "^(.+)$" // TODO // 1 group -> 2 captures

#define XSD_STRING_CAPTURES     1 // wrong but not used
#define XSD_BOOLEAN_CAPTURES    1 // wrong but not used
#define XSD_DECIMAL_CAPTURES    4 // correct and used
#define XSD_INTEGER_CAPTURES    3 // correct and used
#define XSD_FLOAT_CAPTURES      6 // correct and not used
#define XSD_DOUBLE_CAPTURES     XSD_FLOAT_CAPTURES // correct and not used
#define XSD_TIME_CAPTURES       6 // wrong and used
#define XSD_DATE_CAPTURES       6 // wrong and used
#define XSD_DATETIME_CAPTURES   10 // wrong and used
#define XSD_DURATION_CAPTURES   1 // wrong and used

/*
 * dydrad's term_record::construct() only uses:
 *   - xsd_boolean_validate(),
 *   - xsd_int64_value(),
 *   - xsd::decimal::parse(),
 *   - xsd_float_value(),
 *   - xsd_double_value()
 * so for now we do not care about the others... (20250826 mgr)
 */

#endif /* XSDXX_CONST_H */

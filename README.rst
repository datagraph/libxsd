***********************
libxsd++: XSD for C++14
***********************

``libxsd++`` is an XML Schema Datatypes (XSD) library for C++14.

.. image:: https://api.travis-ci.org/datagraph/libxsd.svg?branch=master
   :target: https://travis-ci.org/datagraph/libxsd
   :alt: Travis CI build status

.. image:: https://scan.coverity.com/projects/3277/badge.svg
   :target: https://scan.coverity.com/projects/3277
   :alt: Coverity Scan build status

Features
========

======================= ======================= ================================
Header File             Class Name              XSD Datatype
======================= ======================= ================================
<xsd++/base64.h>        ``xsd::base64``         `xsd:base64Binary`_
<xsd++/boolean.h>       ``xsd::boolean``        `xsd:boolean`_
<xsd++/date.h>          ``xsd::date``           `xsd:date`_
<xsd++/datetime.h>      ``xsd::datetime``       `xsd:dateTime`_
<xsd++/decimal.h>       ``xsd::decimal``        `xsd:decimal`_
<xsd++/double.h>        ``xsd::double``         `xsd:double`_
<xsd++/duration.h>      ``xsd::duration``       `xsd:duration`_ [1]_
<xsd++/float.h>         ``xsd::float``          `xsd:float`_
<xsd++/integer.h>       ``xsd::integer``        `xsd:integer`_ [2]_
<xsd++/string.h>        ``xsd::string``         `xsd:string`_
<xsd++/time.h>          ``xsd::time``           `xsd:time`_
======================= ======================= ================================

.. _xsd:base64Binary:   http://www.w3.org/TR/xmlschema11-2/#base64Binary
.. _xsd:boolean:        http://www.w3.org/TR/xmlschema11-2/#boolean
.. _xsd:date:           http://www.w3.org/TR/xmlschema11-2/#date
.. _xsd:dateTime:       http://www.w3.org/TR/xmlschema11-2/#dateTime
.. _xsd:decimal:        http://www.w3.org/TR/xmlschema11-2/#decimal
.. _xsd:double:         http://www.w3.org/TR/xmlschema11-2/#double
.. _xsd:duration:       http://www.w3.org/TR/xmlschema11-2/#duration
.. _xsd:float:          http://www.w3.org/TR/xmlschema11-2/#float
.. _xsd:integer:        http://www.w3.org/TR/xmlschema11-2/#integer
.. _xsd:string:         http://www.w3.org/TR/xmlschema11-2/#string
.. _xsd:time:           http://www.w3.org/TR/xmlschema11-2/#time

.. rubric:: Footnotes

.. [1] Includes also the derived `xsd:dayTimeDuration`_ and
       `xsd:yearMonthDuration`_ datatypes.

.. [2] Includes also the derived `xsd:long`_, `xsd:int`_, `xsd:short`_, `xsd:byte`_,
       `xsd:unsignedLong`_, `xsd:unsignedInt`_, `xsd:unsignedShort`_,
       `xsd:unsignedByte`_ datatypes.

.. _xsd:dayTimeDuration:   http://www.w3.org/TR/xmlschema11-2/#dayTimeDuration
.. _xsd:yearMonthDuration: http://www.w3.org/TR/xmlschema11-2/#yearMonthDuration

.. _xsd:long:           http://www.w3.org/TR/xmlschema11-2/#long
.. _xsd:int:            http://www.w3.org/TR/xmlschema11-2/#int
.. _xsd:short:          http://www.w3.org/TR/xmlschema11-2/#short
.. _xsd:byte:           http://www.w3.org/TR/xmlschema11-2/#byte
.. _xsd:unsignedLong:   http://www.w3.org/TR/xmlschema11-2/#unsignedLong
.. _xsd:unsignedInt:    http://www.w3.org/TR/xmlschema11-2/#unsignedInt
.. _xsd:unsignedShort:  http://www.w3.org/TR/xmlschema11-2/#unsignedShort
.. _xsd:unsignedByte:   http://www.w3.org/TR/xmlschema11-2/#unsignedByte

References
----------

* `XML Schema Definition Language (XSD) 1.1 Part 2: Datatypes
  <http://www.w3.org/TR/xmlschema11-2/>`__ (2012-04-05)
* `XML Schema Part 2: Datatypes Second Edition
  <http://www.w3.org/TR/xmlschema-2/>`__ (2004-10-28)
* `XPath and XQuery Functions and Operators 3.0
  <http://www.w3.org/TR/xpath-functions-30/>`__ (2014-04-08)
* `XQuery 1.0 and XPath 2.0 Data Model (XDM) (Second Edition)
  <http://www.w3.org/TR/xpath-datamodel/>`__ (2010-12-14)

Build Prerequisites
===================

* Clang_ (>= 3.0) or GCC_ (>= 4.7)
* Autoconf_ (>= 2.68)
* Automake_ (>= 1.11)
* Libtool_ (>= 2.2)

.. _Clang:    http://clang.llvm.org/
.. _GCC:      http://gcc.gnu.org/
.. _Autoconf: http://www.gnu.org/software/autoconf/
.. _Automake: http://www.gnu.org/software/automake/
.. _Libtool:  http://www.gnu.org/software/libtool/

Build Dependencies
==================

* Boost.Regex_ (>= 1.48)

.. _Boost.Regex: http://www.boost.org/libs/regex/

Installation
============

Installing on Unix
------------------

Configuring, building, and installing the library (by default, into
``/usr/local``) are all performed with the standard incantations::

   $ ./autogen.sh                       # for a development checkout only
   $ ./configure                        # on Linux
   $ ./configure --with-stdlib=libc++   # on FreeBSD / Mac OS X
   $ make
   $ sudo make install

Configuration
=============

Configuring a Static Build
--------------------------

By default on most platforms that support both, the library will be built
both as a static library (``libxsd++.a``) as well as a dynamic shared
library (``libxsd++.so`` on most Unix systems, though ``libxsd++.dylib`` on
Darwin).

If you don't require a shared library, configure the build accordingly::

   $ ./configure --disable-shared

Configuring a Minimal Build
---------------------------

The library is thoroughly modular. Specific header files and their
underlying function implementations can be omitted using the familiar
``./configure --disable-FEATURE`` facility provided by Autoconf.

To review the list of features, see the output of ``./configure --help``.

Elsewhere
=========

Find the project at: GitHub_, Bitbucket_, `Travis CI`_, and `Coverity
Scan`_.

.. _GitHub:        http://github.com/datagraph/libxsd
.. _Bitbucket:     http://bitbucket.org/datagraph/libxsd
.. _Travis CI:     http://travis-ci.org/datagraph/libxsd
.. _Coverity Scan: http://scan.coverity.com/projects/3277

Author
======

* `Arto Bendiken <https://github.com/bendiken>`_ - http://ar.to/

License
=======

This is free and unencumbered public domain software. For more information,
see http://unlicense.org/ or the accompanying ``UNLICENSE`` file.

********
libxsd++
********

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

.. _xsd:base64Binary:  http://www.w3.org/TR/xmlschema11-2/#base64Binary
.. _xsd:boolean:       http://www.w3.org/TR/xmlschema11-2/#boolean
.. _xsd:date:          http://www.w3.org/TR/xmlschema11-2/#date
.. _xsd:dateTime:      http://www.w3.org/TR/xmlschema11-2/#dateTime
.. _xsd:decimal:       http://www.w3.org/TR/xmlschema11-2/#decimal
.. _xsd:double:        http://www.w3.org/TR/xmlschema11-2/#double
.. _xsd:duration:      http://www.w3.org/TR/xmlschema11-2/#duration
.. _xsd:float:         http://www.w3.org/TR/xmlschema11-2/#float
.. _xsd:integer:       http://www.w3.org/TR/xmlschema11-2/#integer
.. _xsd:string:        http://www.w3.org/TR/xmlschema11-2/#string
.. _xsd:time:          http://www.w3.org/TR/xmlschema11-2/#time

.. rubric:: Footnotes

.. [1] Includes also the derived datatypes.

.. [2] Includes also the derived `xsd:long`_, `xsd:int`_, `xsd:short`_, `xsd:byte`_,
       `xsd:unsignedLong`_, `xsd:unsignedInt`_, `xsd:unsignedShort`_,
       `xsd:unsignedByte`_ datatypes.

.. _xsd:long:          http://www.w3.org/TR/xmlschema11-2/#long
.. _xsd:int:           http://www.w3.org/TR/xmlschema11-2/#int
.. _xsd:short:         http://www.w3.org/TR/xmlschema11-2/#short
.. _xsd:byte:          http://www.w3.org/TR/xmlschema11-2/#byte
.. _xsd:unsignedLong:  http://www.w3.org/TR/xmlschema11-2/#unsignedLong
.. _xsd:unsignedInt:   http://www.w3.org/TR/xmlschema11-2/#unsignedInt
.. _xsd:unsignedShort: http://www.w3.org/TR/xmlschema11-2/#unsignedShort
.. _xsd:unsignedByte:  http://www.w3.org/TR/xmlschema11-2/#unsignedByte

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

Installation on Unix
====================

::

   $ ./autogen.sh
   $ ./configure                        # on Linux
   $ ./configure --with-stdlib=libc++   # on FreeBSD / Mac OS X
   $ make
   $ sudo make install
   $ sudo ldconfig                      # on Linux

Elsewhere
=========

Find the project at: GitHub_, Bitbucket_, `Travis CI`_, and `Coverity
Scan`_.

.. _GitHub:        http://github.com/datagraph/libxsd
.. _Bitbucket:     http://bitbucket.org/datagraph/libxsd
.. _Travis CI:     http://travis-ci.org/datagraph/libxsd
.. _Coverity Scan: http://scan.coverity.com/projects/3277

## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)

## set python package name
pkgpythondir = $(pyexecdir)/pwgen

## python library
pkgpython_LTLIBRARIES = pwgen.la

pwgen_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_CPPFLAGS)
pwgen_la_SOURCES  = pwgen.cc
pwgen_la_LIBADD   = $(BOOST_PYTHON_LIB)
pwgen_la_LDFLAGS  = -avoid-version
pwgen_la_LDFLAGS += -module

## compile python files
pkgpython_PYTHON = __init__.py

## clean python files
clean-local:
	$(RM) *.pyc

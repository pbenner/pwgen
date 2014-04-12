## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I$(top_srcdir)

## scripts
dist_bin_SCRIPTS = pwgen

## compile python files
pkgpython_PYTHON = pyperclip.py

## python library
pkgpython_LTLIBRARIES = pwgen.la

pwgen_la_CPPFLAGS = $(AM_CPPFLAGS) $(PYTHON_CPPFLAGS)
pwgen_la_SOURCES  = pwgen.cc
pwgen_la_LIBADD   = $(BOOST_PYTHON_LIB)
pwgen_la_LDFLAGS  = -avoid-version
pwgen_la_LDFLAGS += -module

## set python package name
pkgpythondir = $(pyexecdir)

## clean python files
clean-local:
	$(RM) *.pyc

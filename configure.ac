[1]dnl -- configure.ac --
dnl
dnl Copyright (C) 2010-2014 Philipp Benner
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

AC_INIT([pwgen], [1.0], [philipp.benner@mis.mpg.de])
AC_CONFIG_AUX_DIR(auxtools)
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_CONFIG_SRCDIR([auxtools/compile])
dnl we have a README.md instead of a README (foreign)
dnl and we require automake >= 1.12 for bison
AM_INIT_AUTOMAKE([gnu dist-bzip2 foreign 1.12])
dnl find c++ compiler but
dnl turn of AC_PROG_CC's default behaviour
: ${CXXFLAGS=""}
AC_PROG_CXX
dnl run tests (ac_try_compile) for C++ only
AC_LANG([C++])
AC_ISC_POSIX
AC_PROG_INSTALL
AM_PROG_CC_C_O
AC_PROG_LN_S
AM_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL
LT_INIT
LT_PATH_LD

dnl ,---------------------------- 
dnl | GENERAL PACKAGE INFO
dnl `----------------------------

AC_SUBST([PACKAGE_SUMMARY], [""])
AC_SUBST([PACKAGE_URL], [""])
AC_SUBST([PACKAGE_LICENSE], ["GPL"])
AC_SUBST([PACKAGE_DESCRIPTION], [""])

dnl ,---------------------------- 
dnl | PYTHON
dnl `----------------------------

AM_PATH_PYTHON(2.5)
AC_PYTHON_DEVEL

dnl ,---------------------------- 
dnl | BOOST
dnl `----------------------------

AX_BOOST_BASE([1.47.0],,
  AC_MSG_ERROR([this library is required]))
AX_BOOST_PYTHON(,
  AC_MSG_ERROR([this library is required]))

dnl ,---------------------------- 
dnl | DEFINES
dnl `----------------------------

AH_VERBATIM([_GNU_SOURCE],
[/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif])

AC_DEFINE_UNQUOTED(TARGET, "$target",
  [System type this program will compile code for (only needed for compilers).])
AC_DEFINE_UNQUOTED(TARGET_CPU, "$target_cpu",
  [System cpu this program will compile code for (only needed for compilers).])
AC_DEFINE_UNQUOTED(TARGET_OS, "$target_os",
  [Operatins system this program will compile code for (only needed for compilers).])
AC_DEFINE_UNQUOTED(TARGET_VENDOR, "$target_vendor",
  [System vendor type this program will compile code for (only needed for compilers).])

AC_DEFINE_UNQUOTED(BUILD, "$build",
  [System type this program was built on.])
AC_DEFINE_UNQUOTED(BUILD_CPU, "$build_cpu",
  [System cpu this program was built on.])
AC_DEFINE_UNQUOTED(BUILD_OS, "$build_os",
  [Operatins system this program was built on.])
AC_DEFINE_UNQUOTED(BUILD_VENDOR, "$build_vendor",
  [System vendor type this program was built on.])

AC_DEFINE_UNQUOTED(HOST, "$host",
  [System type this program will run on.])
AC_DEFINE_UNQUOTED(HOST_CPU, "$host_cpu",
  [System cpu this program will run on.])
AC_DEFINE_UNQUOTED(HOST_OS, "$host_os",
  [Operatins system this program will run on.])
AC_DEFINE_UNQUOTED(HOST_VENDOR, "$host_vendor",
  [System vendor type this program will run on.])


dnl ,---------------------------- 
dnl | GCC_OPTIONS
dnl `----------------------------

AX_CXX_COMPILE_STDCXX_0X
if test "$ax_cv_cxx_compile_cxx0x_native" = no &&
   test "$ax_cv_cxx_compile_cxx0x_cxx" = yes; then
   CXXFLAGS="$CXXFLAGS -std=gnu++0x"
fi

AX_CXXFLAGS_GCC_OPTION([-Wall])
AX_CXXFLAGS_GCC_OPTION([-Wwrite-strings])
AX_CXXFLAGS_GCC_OPTION([-Wstrict-prototypes])
AX_CXXFLAGS_GCC_OPTION([-Wno-trigraphs])
AX_CXXFLAGS_GCC_OPTION([-Wtrampolines])
AX_CXXFLAGS_GCC_OPTION([-fno-nested-functions])
AX_CXXFLAGS_GCC_OPTION([-fomit-frame-pointer])
AX_CXXFLAGS_GCC_OPTION([-fvisibility-inlines-hidden])

dnl ,---------------------------- 
dnl | AC_OUTPUT
dnl `----------------------------

AC_CONFIG_HEADER([config.h:config.h.in])
AC_CONFIG_FILES([
  Makefile
  pwgen/Makefile
  src/Makefile
  ])

AC_OUTPUT

dnl Local Variables:
dnl indent-tabs-mode: nil
dnl tab-stop-list: (2 4 6 8 10 12 14 16 18 20)
dnl End:

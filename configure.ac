#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.62])
AC_INIT([MediaInfo], [0.1.0], [www.csr.com])
AC_CONFIG_SRCDIR([lib/mediainfo.c])
AC_CONFIG_HEADERS([config.h])
LT_INIT

dnl initialize automake
AM_INIT_AUTOMAKE([-Wno-portability 1.11 no-dist-gzip dist-xz tar-ustar])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

dnl keep this alphabetic per directory, please
AC_CONFIG_FILES(
Makefile
lib/Makefile
test/Makefile
)

AC_OUTPUT

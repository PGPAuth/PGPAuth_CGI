#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(pgpauth_cgi, 1.0, https://github.com/PGPAuth/PGPAuth_CGI/issues)
AM_INIT_AUTOMAKE(pgpauth_cgi, 1.0)
AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AM_PATH_GPGME(1.5.5)
CGICC_CHECK_CONFIG

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale strtol])

AC_OUTPUT(Makefile src/Makefile)

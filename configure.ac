#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(pgpauth_cgi, 1.0, https://github.com/PGPAuth/PGPAuth_CGI/issues)
AM_INIT_AUTOMAKE(pgpauth_cgi, 1.0)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([gpgme], [gpgme_check_version], [], [AC_MSG_ERROR([libgpgme not found.])])
AC_CHECK_LIB([fcgi], [FCGI_Accept], [], [AC_MSG_ERROR([libfcgi not found.])])

PKG_CHECK_MODULES([CGICC], [cgicc >= 3.2.1],,
  AC_MSG_ERROR([libcgicc 3.2.1 or newer not found.])
)

PKG_CHECK_MODULES([LIBCONFIGXX], [libconfig++ >= 1.4],,
  AC_MSG_ERROR([libconfig++ 1.4 or newer not found.])
)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale strtol])

AC_OUTPUT(Makefile src/Makefile)

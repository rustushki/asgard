#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([FULL-PACKAGE-NAME],[VERSION],[BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE(asgard, 0.3.0)
AC_CONFIG_SRCDIR([src/QueryGenerator.cpp])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lsqlite3':
AC_CHECK_LIB([sqlite3], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt assert])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT

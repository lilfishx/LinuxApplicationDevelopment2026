#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0.0], [report@example.com])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([rhash.h readline/readline.h])


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])


AC_CHECK_LIB([rhash], [rhash_library_init], [RHASH_LIBS="-lrhash"], [AC_MSG_ERROR([librhash required])])

AC_ARG_WITH([readline], [], [with_readline=$withval], [with_readline=check])

AS_IF([test "x$with_readline" != "xno"], [
  AC_SEARCH_LIBS([tgetent], [tinfo ncurses termcap window])
  AC_CHECK_LIB([readline], [readline], [
    READLINE_LIBS="-lreadline"
    AC_DEFINE([HAVE_LIBREADLINE],, [Readline active])
    AC_CHECK_LIB([history], [add_history], [READLINE_LIBS="$READLINE_LIBS -lhistory"])
  ], [
    AS_IF([test "x$with_readline" = "xyes"], [AC_MSG_ERROR([readline required])])
  ])
])

AC_SUBST([RHASH_LIBS])
AC_SUBST([READLINE_LIBS])

AC_OUTPUT

AC_PREREQ(2.59)
AC_INIT(alsa-plugins, 1.1.4)
AM_INIT_AUTOMAKE
AC_PREFIX_DEFAULT(/usr)

AM_MAINTAINER_MODE([enable])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_INSTALL
AC_DISABLE_STATIC
AM_PROG_LIBTOOL
AC_HEADER_STDC

CC_NOUNDEFINED

PKG_CHECK_MODULES(ALSA, alsa >= 1.0.11)
AC_CHECK_LIB(asound, snd_pcm_ioplug_create,,
	     AC_ERROR([*** libasound has no external plugin SDK]), -ldl)

AC_ARG_ENABLE([awrate],
      AS_HELP_STRING([--disable-awrate], [Disable building of awrate plugin]))
AS_IF([test "x$enable_awrate" != "xno"],
      [AM_CONDITIONAL(HAVE_AWRATE, true)],
      [AM_CONDITIONAL(HAVE_AWRATE, false)])

AC_ARG_ENABLE([awequal],
      AS_HELP_STRING([--disable-awequal], [Disable building of awequal plugin]))
AS_IF([test "x$enable_awequal" != "xno"],
      [AM_CONDITIONAL(HAVE_AWEQUAL, true)],
      [AM_CONDITIONAL(HAVE_AWEQUAL, false)])

test "x$prefix" = xNONE && prefix=$ac_default_prefix
test "x$exec_prefix" = xNONE && exec_prefix=$prefix

dnl ALSA plugin directory
AC_ARG_WITH(plugindir,
    AS_HELP_STRING([--with-plugindir=dir],
	[path where ALSA plugin files are stored]),
    plugindir="$withval", plugindir="")
if test -z "$plugindir"; then
    eval dir="$libdir"
    case "$dir" in
    /*) ;;
    *) dir="$dir"
    esac
    plugindir="$dir/alsa-lib"
fi
AC_DEFINE_UNQUOTED(ALSA_PLUGIN_DIR, "$plugindir", [directory containing ALSA add-on modules])
ALSA_PLUGIN_DIR="$plugindir"
AC_SUBST(ALSA_PLUGIN_DIR)

dnl ALSA data directory
AC_ARG_WITH(alsadatadir,
    AS_HELP_STRING([--with-alsadatadir=dir],
	[path where ALSA data files are stored]),
    alsadatadir="$withval", alsadatadir="")
if test -z "$alsadatadir"; then
    eval dir="$datadir"
    case "$dir" in
    /*) ;;
    *) dir="$dir"
    esac
    alsadatadir="$dir/alsa"
fi
AC_DEFINE_UNQUOTED(ALSA_DATA_DIR, "$alsadatadir", [directory containing ALSA data files])
ALSA_DATA_DIR="$alsadatadir"
AC_SUBST(ALSA_DATA_DIR)

dnl CPU variant
AC_ARG_WITH(cpuvariant,
    AS_HELP_STRING([--with-cpuvariant=CPU_VARIANT],
    [specify the CPU variant, such as "cortex-a7", "cortex-a53" and so on]),
    cpuvariant="$withval", cpuvariant="")
AC_SUBST(CPU_VARIANT, "$cpuvariant")

dnl C library
AC_ARG_WITH(libc,
    AS_HELP_STRING([--with-libc=LIBC],
    [use which c library, such as "musl" or "glibc"]),
    libc="$withval", libc="")
AC_SUBST(LIBC, "$libc")

SAVE_PLUGINS_VERSION

AC_OUTPUT([
	Makefile
	aw/Makefile
	p-eq/Makefile
])

dnl Show the build conditions

echo
echo "Plugin directory: $ALSA_PLUGIN_DIR"
echo "ALSA_CFLAGS: $ALSA_CFLAGS"
echo "ALSA_LIBS: $ALSA_LIBS"
echo "CPU_VARIANT: $CPU_VARIANT"
echo "LIBC: $LIBC"

/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Where services dir for DBUS is */
#define DBUS_SERVICES_DIR "/usr/local/share/dbus-1/services"

/* always defined to indicate that i18n is enabled */
#define ENABLE_NLS 1

/* Gettext package name */
#define GETTEXT_PACKAGE "hexchat"

/* Prevents using newer APIs */
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_34

/* Dont warn using older APIs */
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_34

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#define HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the `dcgettext' function. */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the `DH_get0_key' function. */
/* #undef HAVE_DH_GET0_KEY */

/* Define to 1 if you have the `DH_set0_key' function. */
/* #undef HAVE_DH_SET0_KEY */

/* Define to 1 if you have the `DH_set0_pqg' function. */
/* #undef HAVE_DH_SET0_PQG */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* #undef HAVE_GTK_MAC */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* iso-codes available */
#define HAVE_ISO_CODES 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `cposix' library (-lcposix). */
/* #undef HAVE_LIBCPOSIX */

/* Define to 1 if you have the `inet' library (-linet). */
/* #undef HAVE_LIBINET */

/* Define to 1 if you have the `net' library (-lnet). */
/* #undef HAVE_LIBNET */

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* #undef HAVE_LIBPCI */

/* Define to 1 if you have the `resolv' library (-lresolv). */
/* #undef HAVE_LIBRESOLV */

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memrchr' function. */
#define HAVE_MEMRCHR 1

/* Define to 1 if you have the <openssl/ssl.h> header file. */
/* #undef HAVE_OPENSSL_SSL_H */

/* If available, contains the Python version number currently in use. */
#define HAVE_PYTHON "2.7"

/* Define to 1 if you have the `SSL_CTX_get_ssl_method' function. */
/* #undef HAVE_SSL_CTX_GET_SSL_METHOD */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `X509_get_signature_nid' function. */
/* #undef HAVE_X509_GET_SIGNATURE_NID */

#define HEXCHATLIBDIR "/usr/local/lib/hexchat/plugins"

#define HEXCHATSHAREDIR "/usr/local/share"

/* ISO codes locale dir */
#define ISO_CODES_LOCALEDIR "/usr/share/locale"

/* ISO codes prefix */
#define ISO_CODES_PREFIX "/usr"

/* Define to 1 if the system uses lookupd */
/* #undef LOOKUPD */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define if debugging is disabled */
#define NDEBUG /**/

/* #undef OLD_PERL */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "HexChat"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "HexChat 2.12.4"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "hexchat"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.12.4"

#define PREFIX "/usr/local"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

#define USE_DBUS 1

/* #undef USE_LIBCANBERRA */

#define USE_LIBNOTIFY 1

/* #undef USE_LIBPROXY */

/* #undef USE_OPENSSL */

#define USE_PLUGIN 1

#define USE_SIGACTION 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* #undef USING_FREEBSD */

#define USING_LINUX 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* #undef socklen_t */

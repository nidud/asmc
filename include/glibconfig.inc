ifndef __G_LIBCONFIG_H__
define __G_LIBCONFIG_H__

include glib/gmacros.inc
include limits.inc
include float.inc

define G_MINFLOAT   FLT_MIN
define G_MAXFLOAT   FLT_MAX
define G_MINDOUBLE  DBL_MIN
define G_MAXDOUBLE  DBL_MAX
define G_MINSHORT   SHRT_MIN
define G_MAXSHORT   SHRT_MAX
define G_MAXUSHORT  USHRT_MAX
define G_MININT     INT_MIN
define G_MAXINT     INT_MAX
define G_MAXUINT    UINT_MAX
define G_MINLONG    LONG_MIN
define G_MAXLONG    LONG_MAX
define G_MAXULONG   ULONG_MAX

gint8   typedef sbyte
guint8  typedef byte
gint16  typedef sword
guint16 typedef word

gint32  typedef sdword
guint32 typedef dword

define G_HAVE_GINT64 1

gint64  typedef sqword
guint64 typedef qword

define GLIB_SIZEOF_VOID_P   8
define GLIB_SIZEOF_LONG     4
define GLIB_SIZEOF_SIZE_T   8
define GLIB_SIZEOF_SSIZE_T  8

gssize  typedef sqword
gsize   typedef qword

define G_MAXSIZE        G_MAXUINT64
define G_MINSSIZE       G_MININT64
define G_MAXSSIZE       G_MAXINT64

goffset typedef gint64

define G_MINOFFSET      G_MININT64
define G_MAXOFFSET      G_MAXINT64

define G_GOFFSET_MODIFIER G_GINT64_MODIFIER
define G_GOFFSET_FORMAT G_GINT64_FORMAT

gintptr typedef sqword
guintptr typedef qword

g_memmove macro dest, src,len
    exitm<memmove((dest), (src), (len))>
    endm

define GLIB_MAJOR_VERSION 2
define GLIB_MINOR_VERSION 72
define GLIB_MICRO_VERSION 1

ifdef __UNIX__
define G_OS_UNIX
define G_HAVE_GNUC_VARARGS
define G_DIR_SEPARATOR          <'/'>
define G_DIR_SEPARATOR_S        <"/">
define G_SEARCHPATH_SEPARATOR   <';'>
define G_SEARCHPATH_SEPARATOR_S <";">
else
define G_HAVE_ISO_VARARGS
define G_OS_WIN32
define G_PLATFORM_WIN32
define G_DIR_SEPARATOR          <'\'>
define G_DIR_SEPARATOR_S        <"\\">
define G_SEARCHPATH_SEPARATOR   <';'>
define G_SEARCHPATH_SEPARATOR_S <";">
endif

define G_CAN_INLINE
define G_HAVE_INLINE
define G_HAVE___INLINE
define G_HAVE___INLINE__

define G_BYTE_ORDER G_LITTLE_ENDIAN

define GLIB_SYSDEF_POLLIN   1
define GLIB_SYSDEF_POLLOUT  4
define GLIB_SYSDEF_POLLPRI  2
define GLIB_SYSDEF_POLLHUP  16
define GLIB_SYSDEF_POLLERR  8
define GLIB_SYSDEF_POLLNVAL 32

GPid    typedef ptr
define G_PID_FORMAT <"p">

define GLIB_SYSDEF_AF_UNIX 1
define GLIB_SYSDEF_AF_INET 2
define GLIB_SYSDEF_AF_INET6 23

define GLIB_SYSDEF_MSG_OOB 1
define GLIB_SYSDEF_MSG_PEEK 2
define GLIB_SYSDEF_MSG_DONTROUTE 4

endif

ifndef __G_LIBCONFIG_H__
define __G_LIBCONFIG_H__

include glib/gmacros.inc
include limits.inc
include float.inc

G_BEGIN_DECLS

GLIB_HAVE_ALLOCA_H  equ 1
GLIB_HAVE_SYS_POLL_H equ 1
GLIB_USING_SYSTEM_PRINTF equ 1

G_MINFLOAT          equ FLT_MIN
G_MAXFLOAT          equ FLT_MAX
G_MINDOUBLE         equ DBL_MIN
G_MAXDOUBLE         equ DBL_MAX
G_MINSHORT          equ SHRT_MIN
G_MAXSHORT          equ SHRT_MAX
G_MAXUSHORT         equ USHRT_MAX
G_MININT            equ INT_MIN
G_MAXINT            equ INT_MAX
G_MAXUINT           equ UINT_MAX
G_MINLONG           equ LONG_MIN
G_MAXLONG           equ LONG_MAX
G_MAXULONG          equ ULONG_MAX

gint8               typedef sbyte
guint8              typedef byte
gint16              typedef sword
guint16             typedef word

G_GINT16_MODIFIER   equ <"h">
G_GINT16_FORMAT     equ <"hi">
G_GUINT16_FORMAT    equ <"hu">

gint32              typedef sdword
guint32             typedef dword

G_GINT32_MODIFIER   equ <"">
G_GINT32_FORMAT     equ <"i">
G_GUINT32_FORMAT    equ <"u">

G_HAVE_GINT64       equ 1 ; deprecated, always true

gint64              typedef sqword
guint64             typedef qword

G_GINT64_CONSTANT   macro val
    exitm<(val)>
    endm
G_GUINT64_CONSTANT  macro val
    exitm<(val)>
    endm

G_GINT64_MODIFIER   equ <"l">
G_GINT64_FORMAT     equ <"li">
G_GUINT64_FORMAT    equ <"lu">

GLIB_SIZEOF_VOID_P  equ size_t
GLIB_SIZEOF_LONG    equ size_t
GLIB_SIZEOF_SIZE_T  equ size_t

gssize              typedef sdword
gsize               typedef dword

G_GSIZE_MODIFIER    equ <"l">
G_GSSIZE_FORMAT     equ <"li">
G_GSIZE_FORMAT      equ <"lu">

G_MAXSIZE           equ G_MAXULONG
G_MINSSIZE          equ G_MINLONG
G_MAXSSIZE          equ G_MAXLONG

goffset             typedef gint64

G_MINOFFSET         equ G_MININT64
G_MAXOFFSET         equ G_MAXINT64
G_GOFFSET_MODIFIER  equ G_GINT64_MODIFIER
G_GOFFSET_FORMAT    equ G_GINT64_FORMAT

G_GOFFSET_CONSTANT  equ <G_GINT64_CONSTANT>

GPOINTER_TO_INT     macro p
    exitm<.err>
    endm
GPOINTER_TO_UINT    macro p
    exitm<.err>
    endm
GINT_TO_POINTER     macro i
    exitm<.err>
    endm
GUINT_TO_POINTER    macro u
    exitm<.err>
    endm

ifdef _WIN64
gintptr             typedef sqword
else
gintptr             typedef sdword
endif
guintptr            typedef size_t

ifdef NeXT
 ;define g_ATEXIT(proc)  (!atexit (proc))
else
; define g_ATEXIT(proc)  (atexit (proc))
endif

g_memmove macro dest, src,len
    exitm<memmove((dest), (src), (len))>
    endm

GLIB_MAJOR_VERSION  equ 2

GLIB_MINOR_VERSION  equ 26
GLIB_MICRO_VERSION  equ 0

G_OS_UNIX           equ 1
G_VA_COPY           equ <va_copy>
G_VA_COPY_AS_ARRAY  equ 1

ifdef  __cplusplus
G_HAVE_INLINE       equ 1
else
G_HAVE_INLINE       equ 1
G_HAVE___INLINE     equ 1
G_HAVE___INLINE__   equ 1
endif

G_CAN_INLINE        equ 1
G_HAVE_ISO_VARARGS  equ 1

G_HAVE_GNUC_VARARGS equ 1
G_HAVE_GROWING_STACK equ 0
G_HAVE_GNUC_VISIBILITY equ 1

G_THREADS_ENABLED   equ 1
G_THREADS_IMPL_POSIX equ 1

GStaticMutex        STRUC
runtime_mutex       ptr_t ?
union static_mutex
  pad               db 40 dup(?)
  dummy_double      double ?
  dummy_pointer     ptr_t ?
  dummy_long        long_t ?
ends
GStaticMutex        ENDS

G_STATIC_MUTEX_INIT equ <{ NULL, { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} } }>

g_static_mutex_get_mutex macro mutex
    exitm<.err>
    endm

GSystemThread       union
  data              db 8 dup(?)
  dummy_double      double ?
  dummy_pointer     ptr_t ?
  dummy_long        long_t ?
GSystemThread       ends

GINT16_TO_LE        macro val
    exitm<.err>
    endm
GUINT16_TO_LE       macro val
    exitm<.err>
    endm
GINT16_TO_BE        macro val
    exitm<.err>
    endm
GUINT16_TO_BE       macro val
    exitm<.err>
    endm
GINT32_TO_LE        macro val
    exitm<.err>
    endm
GUINT32_TO_LE       macro val
    exitm<.err>
    endm
GINT32_TO_BE        macro val
    exitm<.err>
    endm
GUINT32_TO_BE       macro val
    exitm<.err>
    endm
GINT64_TO_LE        macro val
    exitm<.err>
    endm
GUINT64_TO_LE       macro val
    exitm<.err>
    endm
GINT64_TO_BE        macro val
    exitm<.err>
    endm
GUINT64_TO_BE       macro val
    exitm<.err>
    endm
GLONG_TO_LE         macro val
    exitm<.err>
    endm
GULONG_TO_LE        macro val
    exitm<.err>
    endm
GLONG_TO_BE         macro val
    exitm<.err>
    endm
GULONG_TO_BE        macro val
    exitm<.err>
    endm
GINT_TO_LE          macro val
    exitm<.err>
    endm
GUINT_TO_LE         macro val
    exitm<.err>
    endm
GINT_TO_BE          macro val
    exitm<.err>
    endm

.enum AtkTextBoundary {
    TEXT_BOUNDARY_CHAR,
    TEXT_BOUNDARY_WORD_START,
    TEXT_BOUNDARY_WORD_END,
    TEXT_BOUNDARY_SENTENCE_START,
    TEXT_BOUNDARY_SENTENCE_END,
    TEXT_BOUNDARY_LINE_START,
    TEXT_BOUNDARY_LINE_END
}

G_BYTE_ORDER        equ G_LITTLE_ENDIAN
GLIB_SYSDEF_POLLIN  equ 1
GLIB_SYSDEF_POLLOUT equ 4
GLIB_SYSDEF_POLLPRI equ 2
GLIB_SYSDEF_POLLHUP equ 16
GLIB_SYSDEF_POLLERR equ 8
GLIB_SYSDEF_POLLNVAL equ 32
G_MODULE_SUFFIX     equ <"so">

GPid                typedef sdword

GLIB_VERSION_MAX_ALLOWED equ GLIB_VERSION_CUR_STABLE

GLIB_SYSDEF_AF_UNIX     equ 1
GLIB_SYSDEF_AF_INET     equ 2
GLIB_SYSDEF_AF_INET6    equ 23

GLIB_SYSDEF_MSG_OOB     equ 1
GLIB_SYSDEF_MSG_PEEK    equ 2
GLIB_SYSDEF_MSG_DONTROUTE equ 4

endif

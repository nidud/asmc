ifndef __G_TYPES_H__
__G_TYPES_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glibconfig.inc
include glib/gmacros.inc
include glib/gversionmacros.inc
include time.inc

gchar			typedef sbyte
gshort			typedef sword
glong			typedef sdword
gint			typedef sdword
gboolean		typedef gint

guchar			typedef byte
gushort			typedef word
gulong			typedef dword
guint			typedef dword

gfloat			typedef real4
gdouble			typedef real8

G_MININT8		equ -0x80
G_MAXINT8		equ 0x7f
G_MAXUINT8		equ 0xff

G_MININT16		equ -0x8000
G_MAXINT16		equ 0x7fff
G_MAXUINT16		equ 0xffff

G_MININT32		equ -0x80000000
G_MAXINT32		equ 0x7fffffff
G_MAXUINT32		equ 0xffffffff

G_MININT64		equ G_GINT64_CONSTANT(-0x8000000000000000)
G_MAXINT64		equ G_GINT64_CONSTANT(0x7fffffffffffffff)
G_MAXUINT64		equ G_GUINT64_CONSTANT(0xffffffffffffffff)

gpointer		typedef ptr
gconstpointer		typedef ptr

CALLBACKC(GCompareFunc, :gconstpointer, :gconstpointer)
CALLBACKC(GCompareDataFunc, :gconstpointer, :gconstpointer, :gpointer)
CALLBACKC(GEqualFunc, :gconstpointer, :gconstpointer)
CALLBACKC(GDestroyNotify, :gpointer)
CALLBACKC(GFunc, :gpointer, :gpointer)
CALLBACKC(GHashFunc, :gconstpointer)
CALLBACKC(GHFunc, :gpointer, :gpointer, :gpointer)
CALLBACKC(GFreeFunc, :gpointer)
CALLBACKC(GTranslateFunc, :ptr gchar, :gpointer)

G_E			equ 2.7182818284590452353602874713526624977572470937000
G_LN2			equ 0.69314718055994530941723212145817656807550013436026
G_LN10			equ 2.3025850929940456840179914546843642076011014886288
G_PI			equ 3.1415926535897932384626433832795028841971693993751
G_PI_2			equ 1.5707963267948966192313216916397514420985846996876
G_PI_4			equ 0.78539816339744830961566084581987572104929234984378
G_SQRT2			equ 1.4142135623730950488016887242096980785696718753769

G_LITTLE_ENDIAN		equ 1234
G_BIG_ENDIAN		equ 4321
G_PDP_ENDIAN		equ 3412

GTimeVal		STRUC
tv_sec			glong ?
tv_usec			glong ?
GTimeVal		ENDS

endif

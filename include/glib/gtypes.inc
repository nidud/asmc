ifndef __G_TYPES_H__
define __G_TYPES_H__
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

define G_MININT8	(-G_MAXINT8 - 1)
define G_MAXINT8	0x7f
define G_MAXUINT8	0xff


define G_MININT16	(-G_MAXINT16 - 1)
define G_MAXINT16	0x7fff
define G_MAXUINT16	0xffff


define G_MININT32	(-G_MAXINT32 - 1)
define G_MAXINT32	0x7fffffff
define G_MAXUINT32	0xffffffff


define G_MININT64	(-G_MAXINT64 - G_GINT64_CONSTANT(1))
define G_MAXINT64	G_GINT64_CONSTANT(0x7fffffffffffffff)
define G_MAXUINT64	G_GUINT64_CONSTANT(0xffffffffffffffff)

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

define G_E     2.7182818284590452353602874713526624977572470937000
define G_LN2   0.69314718055994530941723212145817656807550013436026
define G_LN10  2.3025850929940456840179914546843642076011014886288
define G_PI    3.1415926535897932384626433832795028841971693993751
define G_PI_2  1.5707963267948966192313216916397514420985846996876
define G_PI_4  0.78539816339744830961566084581987572104929234984378
define G_SQRT2 1.4142135623730950488016887242096980785696718753769

define G_LITTLE_ENDIAN 1234
define G_BIG_ENDIAN    4321
define G_PDP_ENDIAN    3412

GTimeVal		STRUC
tv_sec			glong ?
tv_usec			glong ?
GTimeVal		ENDS

endif

ifndef __GDK_RGBA_H__
__GDK_RGBA_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

GdkRGBA			STRUC
red			gdouble ?
green			gdouble ?
blue			gdouble ?
alpha			gdouble ?
GdkRGBA			ENDS

GDK_TYPE_RGBA		equ <gdk_rgba_get_type>

;GType
gdk_rgba_get_type proto __cdecl

;GdkRGBA
gdk_rgba_copy proto __cdecl \
		  rgba: ptr GdkRGBA

;void
gdk_rgba_free proto __cdecl \
		  rgba: ptr GdkRGBA


;guint
gdk_rgba_hash proto __cdecl \
		     p: gconstpointer

;gboolean
gdk_rgba_equal proto __cdecl \
		    p1: gconstpointer,
		    p2: gconstpointer

;gboolean
gdk_rgba_parse proto __cdecl \
		  rgba: ptr GdkRGBA,
		  spec: ptr gchar

;gchar
gdk_rgba_to_string proto __cdecl \
		  rgba: ptr GdkRGBA

endif

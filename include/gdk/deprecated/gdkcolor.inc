ifndef __GDK_COLOR_H__
__GDK_COLOR_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

;include cairo.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

GdkColor		STRUC
pixel			guint32 ?
red			guint16 ?
green			guint16 ?
blue			guint16 ?
GdkColor		ENDS

GDK_TYPE_COLOR		equ <gdk_color_get_type>

;GType
gdk_color_get_type proto __cdecl

;GdkColor
gdk_color_copy proto __cdecl \
		 color: ptr GdkColor

;void
gdk_color_free proto __cdecl \
		 color: ptr GdkColor


;guint
gdk_color_hash proto __cdecl \
		 color: ptr GdkColor

;gboolean
gdk_color_equal proto __cdecl \
		colora: ptr GdkColor,
		colorb: ptr GdkColor


;gboolean
gdk_color_parse proto __cdecl \
		  spec: ptr gchar,
		 color: ptr GdkColor

;gchar
gdk_color_to_string proto __cdecl \
		 color: ptr GdkColor

endif

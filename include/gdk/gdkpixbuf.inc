ifndef __GDK_PIXBUF_H__
__GDK_PIXBUF_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

;include cairo.inc
;include gdk-pixbuf/gdk-pixbuf.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;GdkPixbuf
gdk_pixbuf_get_from_window proto __cdecl \
                window: ptr GdkWindow,
                 src_x: gint,
                 src_y: gint,
                 width: gint,
                height: gint


;GdkPixbuf
gdk_pixbuf_get_from_surface proto __cdecl \
               surface: ptr cairo_surface_t,
                 src_x: gint,
                 src_y: gint,
                 width: gint,
                height: gint

endif

ifndef __GDK_PANGO_H__
__GDK_PANGO_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;PangoContext
gdk_pango_context_get_for_screen proto __cdecl \
                screen: ptr GdkScreen

;PangoContext
gdk_pango_context_get proto __cdecl

;cairo_region_t
gdk_pango_layout_line_get_clip_region proto __cdecl \
                  line: ptr PangoLayoutLine,
              x_origin: gint,
              y_origin: gint,
          index_ranges: ptr gint,
              n_ranges: gint

;cairo_region_t
gdk_pango_layout_get_clip_region proto __cdecl \
                layout: ptr PangoLayout,
              x_origin: gint,
              y_origin: gint,
          index_ranges: ptr gint,
              n_ranges: gint

endif

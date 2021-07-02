ifndef __GDK_CAIRO_H__
__GDK_CAIRO_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/deprecated/gdkcolor.inc
include gdk/gdkrgba.inc
include gdk/gdkpixbuf.inc
;include pango/pangocairo.inc

;cairo_t
gdk_cairo_create proto __cdecl \
                window: ptr GdkWindow

;gboolean
gdk_cairo_get_clip_rectangle proto __cdecl \
                    cr: ptr cairo_t,
                  rect: ptr GdkRectangle

;void
gdk_cairo_set_source_rgba proto __cdecl \
                    cr: ptr cairo_t,
                  rgba: ptr GdkRGBA

;void
gdk_cairo_set_source_pixbuf proto __cdecl \
                    cr: ptr cairo_t,
                pixbuf: ptr GdkPixbuf,
              pixbuf_x: gdouble,
              pixbuf_y: gdouble

;void
gdk_cairo_set_source_window proto __cdecl \
                    cr: ptr cairo_t,
                window: ptr GdkWindow,
                     x: gdouble,
                     y: gdouble

;void
gdk_cairo_rectangle proto __cdecl \
                    cr: ptr cairo_t,
             rectangle: ptr GdkRectangle

;void
gdk_cairo_region proto __cdecl \
                    cr: ptr cairo_t,
                region: ptr cairo_region_t


;cairo_region_t
gdk_cairo_region_create_from_surface proto __cdecl \
               surface: ptr cairo_surface_t


;void
gdk_cairo_set_source_color proto __cdecl \
                    cr: ptr cairo_t,
                 color: ptr GdkColor


;cairo_surface_t
gdk_cairo_surface_create_from_pixbuf proto __cdecl \
                pixbuf: ptr GdkPixbuf,
                 scale: int_t,
            for_window: ptr GdkWindow

;void
gdk_cairo_draw_from_gl proto __cdecl \
                    cr: ptr cairo_t,
                window: ptr GdkWindow,
                source: int_t,
           source_type: int_t,
          buffer_scale: int_t,
                     x: int_t,
                     y: int_t,
                 width: int_t,
                height: int_t


endif

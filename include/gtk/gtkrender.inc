ifndef __GTK_RENDER_H__
__GTK_RENDER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;include cairo.inc
;include pango/pango.inc
include gdk/gdk.inc

include gtk/gtkenums.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

;void
gtk_render_check proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_option proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_arrow proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                 angle: gdouble,
                     x: gdouble,
                     y: gdouble,
                  size: gdouble

;void
gtk_render_background proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_frame proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_expander proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_focus proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_layout proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                layout: ptr PangoLayout

;void
gtk_render_line proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                    x0: gdouble,
                    y0: gdouble,
                    x1: gdouble,
                    y1: gdouble

;void
gtk_render_slider proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble,
           orientation: GtkOrientation

;void
gtk_render_frame_gap proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble,
              gap_side: GtkPositionType,
               xy0_gap: gdouble,
               xy1_gap: gdouble

;void
gtk_render_extension proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble,
              gap_side: GtkPositionType

;void
gtk_render_handle proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;void
gtk_render_activity proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                     x: gdouble,
                     y: gdouble,
                 width: gdouble,
                height: gdouble

;GdkPixbuf
gtk_render_icon_pixbuf proto __cdecl \
               context: ptr GtkStyleContext,
                source: ptr GtkIconSource,
                  size: GtkIconSize

;void
gtk_render_icon proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
                pixbuf: ptr GdkPixbuf,
                     x: gdouble,
                     y: gdouble

;void
gtk_render_icon_surface proto __cdecl \
               context: ptr GtkStyleContext,
                    cr: ptr cairo_t,
               surface: ptr cairo_surface_t,
                     x: gdouble,
                     y: gdouble


G_END_DECLS

endif

ifndef __GTK_COLOR_UTILS_H__
__GTK_COLOR_UTILS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gdk/gdk.inc

G_BEGIN_DECLS

gtk_hsv_to_rgb proto __cdecl \
                     h: gdouble,
                     s: gdouble,
                     v: gdouble,
                     r: ptr gdouble,
                     g: ptr gdouble,
                     b: ptr gdouble

gtk_rgb_to_hsv proto __cdecl \
                     r: gdouble,
                     g: gdouble,
                     b: gdouble,
                     h: ptr gdouble,
                     s: ptr gdouble,
                     v: ptr gdouble

G_END_DECLS

endif

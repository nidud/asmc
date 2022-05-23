ifndef __GDK_CAIRO_H__
define __GDK_CAIRO_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdkrgba.inc
include gdk/gdkpixbuf.inc
include pango/pangocairo.inc

gdk_cairo_set_source_rgba proto :ptr, :ptr
gdk_cairo_set_source_pixbuf proto :ptr, :ptr, :real8, :real8
gdk_cairo_rectangle proto :ptr, :ptr
gdk_cairo_region proto :ptr, :ptr

gdk_cairo_region_create_from_surface proto :ptr

gdk_cairo_draw_from_gl proto :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword

endif

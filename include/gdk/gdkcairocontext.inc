ifndef __GDK_CAIRO_CONTEXT__
define __GDK_CAIRO_CONTEXT__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include cairo.inc

define GDK_TYPE_CAIRO_CONTEXT             <gdk_cairo_context_get_type ()>

GDK_CAIRO_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_CAIRO_CONTEXT, GdkCairoContext))>
  endm
GDK_IS_CAIRO_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_CAIRO_CONTEXT))>
  endm

define GDK_CAIRO_ERROR                    <gdk_cairo_error_quark ()>

gdk_cairo_context_get_type proto
gdk_cairo_context_cairo_create proto :ptr

endif




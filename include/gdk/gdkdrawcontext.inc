ifndef __GDK_DRAW_CONTEXT__
define __GDK_DRAW_CONTEXT__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_DRAW_CONTEXT <gdk_draw_context_get_type ()>
GDK_DRAW_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_DRAW_CONTEXT, GdkDrawContext))>
  endm
GDK_IS_DRAW_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_DRAW_CONTEXT))>
  endm

gdk_draw_context_get_type proto
gdk_draw_context_get_display proto :ptr
gdk_draw_context_get_surface proto :ptr
gdk_draw_context_begin_frame proto :ptr, :ptr
gdk_draw_context_end_frame proto :ptr
gdk_draw_context_is_in_frame proto :ptr
gdk_draw_context_get_frame_region proto :ptr


endif

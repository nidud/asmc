ifndef __GDK_CURSOR_H__
define __GDK_CURSOR_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_CURSOR              <gdk_cursor_get_type ()>
GDK_CURSOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_CURSOR, GdkCursor))>
  endm
GDK_IS_CURSOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_CURSOR))>
  endm


gdk_cursor_get_type proto
gdk_cursor_new_from_texture proto :ptr, :sdword, :sdword, :ptr
gdk_cursor_new_from_name proto :ptr, :ptr
gdk_cursor_get_fallback proto :ptr
gdk_cursor_get_name proto :ptr
gdk_cursor_get_texture proto :ptr
gdk_cursor_get_hotspot_x proto :ptr
gdk_cursor_get_hotspot_y proto :ptr

endif

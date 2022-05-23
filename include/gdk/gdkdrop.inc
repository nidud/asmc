ifndef __GDK_DROP_H__
define __GDK_DROP_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkenums.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

define GDK_TYPE_DROP              <gdk_drop_get_type>
GDK_DROP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DROP, GdkDrop))>
  endm
GDK_IS_DROP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DROP))>
  endm

gdk_drop_get_type proto

gdk_drop_get_display proto :ptr
gdk_drop_get_device proto :ptr
gdk_drop_get_surface proto :ptr
gdk_drop_get_formats proto :ptr
gdk_drop_get_actions proto :ptr
gdk_drop_get_drag proto :ptr

gdk_drop_status proto :ptr, :GdkDragAction, :GdkDragAction
gdk_drop_finish proto :ptr, :GdkDragAction

gdk_drop_read_async proto :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_drop_read_finish proto :ptr, :ptr, :ptr, :ptr
gdk_drop_read_value_async proto :ptr, :GType, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_drop_read_value_finish proto :ptr, :ptr, :ptr


endif

ifndef __GDK_DND_H__
define __GDK_DND_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkdevice.inc
include gdk/gdkenums.inc
include gdk/gdkevents.inc
include gdk/gdktypes.inc

define GDK_TYPE_DRAG <gdk_drag_get_type ()>
GDK_DRAG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DRAG, GdkDrag))>
  endm
GDK_IS_DRAG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DRAG))>
  endm

.enum GdkDragCancelReason {
  GDK_DRAG_CANCEL_NO_TARGET,
  GDK_DRAG_CANCEL_USER_CANCELLED,
  GDK_DRAG_CANCEL_ERROR
}

gdk_drag_get_type proto
gdk_drag_get_display proto :ptr
gdk_drag_get_device proto :ptr
gdk_drag_get_formats proto :ptr
gdk_drag_get_actions proto :ptr
gdk_drag_get_selected_action proto :ptr
gdk_drag_action_is_unique proto :GdkDragAction
gdk_drag_begin proto :ptr, :ptr, :ptr, :GdkDragAction, :real8, :real8
gdk_drag_drop_done proto :ptr, :gboolean
gdk_drag_get_drag_surface proto :ptr
gdk_drag_set_hotspot proto :ptr, :sdword, :sdword
gdk_drag_get_content proto :ptr
gdk_drag_get_surface proto :ptr

endif

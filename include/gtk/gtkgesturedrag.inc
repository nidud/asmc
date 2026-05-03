ifndef __GTK_GESTURE_DRAG_H__
define __GTK_GESTURE_DRAG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkgesturesingle.inc

define GTK_TYPE_GESTURE_DRAG <gtk_gesture_drag_get_type ()>
GTK_GESTURE_DRAG macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_DRAG, GtkGestureDrag))>
  endm
GTK_GESTURE_DRAG_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_DRAG, GtkGestureDragClass))>
  endm
GTK_IS_GESTURE_DRAG macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_DRAG))>
  endm
GTK_IS_GESTURE_DRAG_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_DRAG))>
  endm
GTK_GESTURE_DRAG_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_DRAG, GtkGestureDragClass))>
  endm

gtk_gesture_drag_get_type proto
gtk_gesture_drag_new proto
gtk_gesture_drag_get_start_point proto :ptr, :ptr, :ptr
gtk_gesture_drag_get_offset proto :ptr, :ptr, :ptr

endif

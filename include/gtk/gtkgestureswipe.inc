ifndef __GTK_GESTURE_SWIPE_H__
define __GTK_GESTURE_SWIPE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkgesturesingle.inc

define GTK_TYPE_GESTURE_SWIPE <gtk_gesture_swipe_get_type ()>
GTK_GESTURE_SWIPE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_SWIPE, GtkGestureSwipe))>
  endm
GTK_GESTURE_SWIPE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_SWIPE, GtkGestureSwipeClass))>
  endm
GTK_IS_GESTURE_SWIPE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_SWIPE))>
  endm
GTK_IS_GESTURE_SWIPE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_SWIPE))>
  endm
GTK_GESTURE_SWIPE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_SWIPE, GtkGestureSwipeClass))>
  endm

gtk_gesture_swipe_get_type proto
gtk_gesture_swipe_new proto
gtk_gesture_swipe_get_velocity proto :ptr, :ptr, :ptr

endif

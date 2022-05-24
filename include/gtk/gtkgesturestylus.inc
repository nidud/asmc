ifndef __GTK_GESTURE_STYLUS_H__
define __GTK_GESTURE_STYLUS_H__

include gtk/gtkgesture.inc

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

define GTK_TYPE_GESTURE_STYLUS <gtk_gesture_stylus_get_type ()>
GTK_GESTURE_STYLUS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_STYLUS, GtkGestureStylus))>
  endm
GTK_GESTURE_STYLUS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_STYLUS, GtkGestureStylusClass))>
  endm
GTK_IS_GESTURE_STYLUS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_STYLUS))>
  endm
GTK_IS_GESTURE_STYLUS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_STYLUS))>
  endm
GTK_GESTURE_STYLUS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_STYLUS, GtkGestureStylusClass))>
  endm

;GtkGestureStylus        typedef _GtkGestureStylus
;GtkGestureStylusClass   typedef _GtkGestureStylusClass

gtk_gesture_stylus_get_type proto
gtk_gesture_stylus_new proto
gtk_gesture_stylus_get_axis proto :ptr, :GdkAxisUse, :ptr
gtk_gesture_stylus_get_axes proto :ptr, :GdkAxisUse, :ptr
gtk_gesture_stylus_get_backlog proto :ptr, :ptr, :ptr
gtk_gesture_stylus_get_device_tool proto :ptr

endif

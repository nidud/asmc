ifndef __GTK_GESTURE_PAN_H__
define __GTK_GESTURE_PAN_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkenums.inc
include gtk/gtkgesturedrag.inc

define GTK_TYPE_GESTURE_PAN <gtk_gesture_pan_get_type ()>
GTK_GESTURE_PAN macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_PAN, GtkGesturePan))>
  endm
GTK_GESTURE_PAN_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_PAN, GtkGesturePanClass))>
  endm
GTK_IS_GESTURE_PAN macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_PAN))>
  endm
GTK_IS_GESTURE_PAN_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_PAN))>
  endm
GTK_GESTURE_PAN_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_PAN, GtkGesturePanClass))>
  endm

;GtkGesturePan           typedef _GtkGesturePan
;GtkGesturePanClass      typedef _GtkGesturePanClass

gtk_gesture_pan_get_type proto
gtk_gesture_pan_new proto :GtkOrientation
gtk_gesture_pan_get_orientation proto :ptr
gtk_gesture_pan_set_orientation proto :ptr, :GtkOrientation

endif

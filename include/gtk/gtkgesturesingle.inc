ifndef __GTK_GESTURE_SINGLE_H__
define __GTK_GESTURE_SINGLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkgesture.inc

define GTK_TYPE_GESTURE_SINGLE <gtk_gesture_single_get_type ()>
GTK_GESTURE_SINGLE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_SINGLE, GtkGestureSingle))>
  endm
GTK_GESTURE_SINGLE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_SINGLE, GtkGestureSingleClass))>
  endm
GTK_IS_GESTURE_SINGLE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_SINGLE))>
  endm
GTK_IS_GESTURE_SINGLE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_SINGLE))>
  endm
GTK_GESTURE_SINGLE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_SINGLE, GtkGestureSingleClass))>
  endm

;GtkGestureSingle        typedef _GtkGestureSingle
;GtkGestureSingleClass   typedef _GtkGestureSingleClass

gtk_gesture_single_get_type proto
gtk_gesture_single_get_touch_only proto :ptr
gtk_gesture_single_set_touch_only proto :ptr, :gboolean
gtk_gesture_single_get_exclusive proto :ptr
gtk_gesture_single_set_exclusive proto :ptr, :gboolean
gtk_gesture_single_get_button proto :ptr
gtk_gesture_single_set_button proto :ptr, :guint
gtk_gesture_single_get_current_button proto :ptr
gtk_gesture_single_get_current_sequence proto :ptr

endif

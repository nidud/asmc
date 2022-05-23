ifndef __GTK_GESTURE_H__
define __GTK_GESTURE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeventcontroller.inc
include gtk/gtkenums.inc

define GTK_TYPE_GESTURE <gtk_gesture_get_type>
GTK_GESTURE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE, GtkGesture))>
  endm
GTK_GESTURE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE, GtkGestureClass))>
  endm
GTK_IS_GESTURE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE))>
  endm
GTK_IS_GESTURE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE))>
  endm
GTK_GESTURE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE, GtkGestureClass))>
  endm

;GtkGestureClass         typedef _GtkGestureClass

gtk_gesture_get_type proto
gtk_gesture_get_device proto :ptr
gtk_gesture_set_state proto :ptr, :GtkEventSequenceState
gtk_gesture_set_sequence_state proto :ptr, :ptr, :GtkEventSequenceState
gtk_gesture_get_sequences proto :ptr
gtk_gesture_get_last_updated_sequence proto :ptr
gtk_gesture_handles_sequence proto :ptr, :ptr
gtk_gesture_get_point proto :ptr, :ptr, :ptr, :ptr
gtk_gesture_get_bounding_box proto :ptr, :ptr
gtk_gesture_get_bounding_box_center proto :ptr, :ptr, :ptr
gtk_gesture_is_active proto :ptr
gtk_gesture_is_recognized proto :ptr
gtk_gesture_group proto :ptr, :ptr
gtk_gesture_ungroup proto :ptr
gtk_gesture_get_group proto :ptr
gtk_gesture_is_grouped_with proto :ptr, :ptr

endif

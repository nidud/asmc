ifndef __GTK_GESTURE_H__
__GTK_GESTURE_H__ equ <>

if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeventcontroller.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE equ <gtk_gesture_get_type>
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

;GType
gtk_gesture_get_type proto __cdecl

;GdkDevice
gtk_gesture_get_device proto __cdecl \
	       gesture: ptr GtkGesture


;gboolean
gtk_gesture_set_state proto __cdecl \
	       gesture: ptr GtkGesture,
		 state: GtkEventSequenceState

;GtkEventSequenceState
gtk_gesture_get_sequence_state proto __cdecl \
	       gesture: ptr GtkGesture,
	      sequence: ptr GdkEventSequence

;gboolean
gtk_gesture_set_sequence_state proto __cdecl \
	       gesture: ptr GtkGesture,
	      sequence: ptr GdkEventSequence,
		 state: GtkEventSequenceState

;GList
gtk_gesture_get_sequences proto __cdecl \
	       gesture: ptr GtkGesture


;GdkEventSequence
gtk_gesture_get_last_updated_sequence proto __cdecl \
	       gesture: ptr GtkGesture


;gboolean
gtk_gesture_handles_sequence proto __cdecl \
	       gesture: ptr GtkGesture,
	      sequence: ptr GdkEventSequence

;const
gtk_gesture_get_last_event proto __cdecl \
	       gesture: ptr GtkGesture,
	      sequence: ptr GdkEventSequence

;gboolean
gtk_gesture_get_point proto __cdecl \
	       gesture: ptr GtkGesture,
	      sequence: ptr GdkEventSequence,
		     x: ptr gdouble,
		     y: ptr gdouble

;gboolean
gtk_gesture_get_bounding_box proto __cdecl \
	       gesture: ptr GtkGesture,
		  rect: ptr GdkRectangle

;gboolean
gtk_gesture_get_bounding_box_center proto __cdecl \
	       gesture: ptr GtkGesture,
		     x: ptr gdouble,
		     y: ptr gdouble

;gboolean
gtk_gesture_is_active proto __cdecl \
	       gesture: ptr GtkGesture


;gboolean
gtk_gesture_is_recognized proto __cdecl \
	       gesture: ptr GtkGesture


;GdkWindow
gtk_gesture_get_window proto __cdecl \
	       gesture: ptr GtkGesture


;void
gtk_gesture_set_window proto __cdecl \
	       gesture: ptr GtkGesture,
		window: ptr GdkWindow


;void
gtk_gesture_group proto __cdecl \
	 group_gesture: ptr GtkGesture,
	       gesture: ptr GtkGesture

;void
gtk_gesture_ungroup proto __cdecl \
	       gesture: ptr GtkGesture


;GList
gtk_gesture_get_group proto __cdecl \
	       gesture: ptr GtkGesture


;gboolean
gtk_gesture_is_grouped_with proto __cdecl \
	       gesture: ptr GtkGesture,
		 other: ptr GtkGesture

G_END_DECLS

endif

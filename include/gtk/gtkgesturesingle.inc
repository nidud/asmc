ifndef __GTK_GESTURE_SINGLE_H__
__GTK_GESTURE_SINGLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkgesture.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE_SINGLE equ <gtk_gesture_single_get_type>
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

;GType
gtk_gesture_single_get_type proto __cdecl

;gboolean
gtk_gesture_single_get_touch_only proto __cdecl \
	       gesture: ptr GtkGestureSingle


;void
gtk_gesture_single_set_touch_only proto __cdecl \
	       gesture: ptr GtkGestureSingle,
	    touch_only: gboolean

;gboolean
gtk_gesture_single_get_exclusive proto __cdecl \
	       gesture: ptr GtkGestureSingle


;void
gtk_gesture_single_set_exclusive proto __cdecl \
	       gesture: ptr GtkGestureSingle,
	     exclusive: gboolean


;guint
gtk_gesture_single_get_button proto __cdecl \
	       gesture: ptr GtkGestureSingle


;void
gtk_gesture_single_set_button proto __cdecl \
	       gesture: ptr GtkGestureSingle,
		button: guint


;guint
gtk_gesture_single_get_current_button proto __cdecl \
	       gesture: ptr GtkGestureSingle


;GdkEventSequence
gtk_gesture_single_get_current_sequence proto __cdecl \
	       gesture: ptr GtkGestureSingle


G_END_DECLS

endif

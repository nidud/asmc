ifndef __GTK_GESTURE_ROTATE_H__
__GTK_GESTURE_ROTATE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkgesture.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE_ROTATE equ <gtk_gesture_rotate_get_type>
GTK_GESTURE_ROTATE macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_ROTATE, GtkGestureRotate))>
	endm
GTK_GESTURE_ROTATE_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_ROTATE, GtkGestureRotateClass))>
	endm
GTK_IS_GESTURE_ROTATE macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_ROTATE))>
	endm
GTK_IS_GESTURE_ROTATE_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_ROTATE))>
	endm
GTK_GESTURE_ROTATE_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_ROTATE, GtkGestureRotateClass))>
	endm

;GType
gtk_gesture_rotate_get_type proto __cdecl

;GtkGesture
gtk_gesture_rotate_new proto __cdecl \
		widget: ptr GtkWidget


;gdouble
gtk_gesture_rotate_get_angle_delta proto __cdecl \
	       gesture: ptr GtkGestureRotate


G_END_DECLS

endif

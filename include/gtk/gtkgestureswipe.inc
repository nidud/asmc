ifndef __GTK_GESTURE_SWIPE_H__
__GTK_GESTURE_SWIPE_H__ equ <>

if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkgesturesingle.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE_SWIPE equ <gtk_gesture_swipe_get_type>
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

;GType
gtk_gesture_swipe_get_type proto __cdecl

;GtkGesture
gtk_gesture_swipe_new proto __cdecl \
		widget: ptr GtkWidget


;gboolean
gtk_gesture_swipe_get_velocity proto __cdecl \
	       gesture: ptr GtkGestureSwipe,
	    velocity_x: ptr gdouble,
	    velocity_y: ptr gdouble


G_END_DECLS

endif

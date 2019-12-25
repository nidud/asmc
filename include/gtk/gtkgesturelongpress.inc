ifndef __GTK_GESTURE_LONG_PRESS_H__
__GTK_GESTURE_LONG_PRESS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkgesturesingle.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE_LONG_PRESS equ (gtk_gesture_long_press_get_type ())
GTK_GESTURE_LONG_PRESS macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_LONG_PRESS, GtkGestureLongPress))>
	endm
GTK_GESTURE_LONG_PRESS_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_LONG_PRESS, GtkGestureLongPressClass))>
	endm
GTK_IS_GESTURE_LONG_PRESS macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_LONG_PRESS))>
	endm
GTK_IS_GESTURE_LONG_PRESS_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_LONG_PRESS))>
	endm
GTK_GESTURE_LONG_PRESS_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_LONG_PRESS, GtkGestureLongPressClass))>
	endm

;GType
gtk_gesture_long_press_get_type proto __cdecl

;GtkGesture
gtk_gesture_long_press_new proto __cdecl \
		widget: ptr GtkWidget

G_END_DECLS

endif

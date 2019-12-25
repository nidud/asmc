ifndef __GTK_GESTURE_ZOOM_H__
__GTK_GESTURE_ZOOM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkgesture.inc
include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_GESTURE_ZOOM equ <gtk_gesture_zoom_get_type>
GTK_GESTURE_ZOOM macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_ZOOM, GtkGestureZoom))>
	endm
GTK_GESTURE_ZOOM_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_ZOOM, GtkGestureZoomClass))>
	endm
GTK_IS_GESTURE_ZOOM macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_ZOOM))>
	endm
GTK_IS_GESTURE_ZOOM_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_ZOOM))>
	endm
GTK_GESTURE_ZOOM_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_ZOOM, GtkGestureZoomClass))>
	endm

;GType
gtk_gesture_zoom_get_type proto __cdecl

;GtkGesture
gtk_gesture_zoom_new proto __cdecl \
		widget: ptr GtkWidget


;gdouble
gtk_gesture_zoom_get_scale_delta proto __cdecl \
	       gesture: ptr GtkGestureZoom


G_END_DECLS

endif

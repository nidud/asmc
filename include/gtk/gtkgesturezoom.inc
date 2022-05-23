ifndef __GTK_GESTURE_ZOOM_H__
define __GTK_GESTURE_ZOOM_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkgesture.inc
include gtk/gtkwidget.inc

define GTK_TYPE_GESTURE_ZOOM <gtk_gesture_zoom_get_type>
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

;GtkGestureZoom          typedef _GtkGestureZoom
;GtkGestureZoomClass     typedef _GtkGestureZoomClass

gtk_gesture_zoom_get_type proto
gtk_gesture_zoom_new proto
gtk_gesture_zoom_get_scale_delta proto :ptr

endif

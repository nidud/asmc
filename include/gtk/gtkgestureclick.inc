ifndef __GTK_GESTURE_CLICK_H__
define __GTK_GESTURE_CLICK_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkgesturesingle.inc

define GTK_TYPE_GESTURE_CLICK <gtk_gesture_click_get_type ()>
GTK_GESTURE_CLICK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GESTURE_CLICK, GtkGestureClick))>
  endm
GTK_GESTURE_CLICK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GESTURE_CLICK, GtkGestureClickClass))>
  endm
GTK_IS_GESTURE_CLICK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GESTURE_CLICK))>
  endm
GTK_IS_GESTURE_CLICK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GESTURE_CLICK))>
  endm
GTK_GESTURE_CLICK_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GESTURE_CLICK, GtkGestureClickClass))>
  endm

;GtkGestureClick         typedef _GtkGestureClick
;GtkGestureClickClass    typedef _GtkGestureClickClass

gtk_gesture_click_get_type proto
gtk_gesture_click_new proto

endif

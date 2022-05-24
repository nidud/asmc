ifndef __GTK_EVENT_CONTROLLER_MOTION_H__
define __GTK_EVENT_CONTROLLER_MOTION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc

define GTK_TYPE_EVENT_CONTROLLER_MOTION <gtk_event_controller_motion_get_type ()>
GTK_EVENT_CONTROLLER_MOTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER_MOTION, GtkEventControllerMotion))>
  endm
GTK_EVENT_CONTROLLER_MOTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER_MOTION, GtkEventControllerMotionClass))>
  endm
GTK_IS_EVENT_CONTROLLER_MOTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER_MOTION))>
  endm
GTK_IS_EVENT_CONTROLLER_MOTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER_MOTION))>
  endm
GTK_EVENT_CONTROLLER_MOTION_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER_MOTION, GtkEventControllerMotionClass))>
  endm

;GtkEventControllerMotion typedef _GtkEventControllerMotion
;GtkEventControllerMotionClass typedef _GtkEventControllerMotionClass

gtk_event_controller_motion_get_type proto
gtk_event_controller_motion_new proto
gtk_event_controller_motion_contains_pointer proto :ptr
gtk_event_controller_motion_is_pointer proto :ptr

endif

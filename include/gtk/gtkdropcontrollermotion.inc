ifndef __GTK_DROP_CONTROLLER_MOTION_H__
define __GTK_DROP_CONTROLLER_MOTION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc

define GTK_TYPE_DROP_CONTROLLER_MOTION <gtk_drop_controller_motion_get_type ()>
GTK_DROP_CONTROLLER_MOTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_DROP_CONTROLLER_MOTION, GtkDropControllerMotion))>
  endm
GTK_DROP_CONTROLLER_MOTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_DROP_CONTROLLER_MOTION, GtkDropControllerMotionClass))>
  endm
GTK_IS_DROP_CONTROLLER_MOTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_DROP_CONTROLLER_MOTION))>
  endm
GTK_IS_DROP_CONTROLLER_MOTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_DROP_CONTROLLER_MOTION))>
  endm
GTK_DROP_CONTROLLER_MOTION_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_DROP_CONTROLLER_MOTION, GtkDropControllerMotionClass))>
  endm

;GtkDropControllerMotion typedef _GtkDropControllerMotion
;GtkDropControllerMotionClass typedef _GtkDropControllerMotionClass

gtk_drop_controller_motion_get_type proto
gtk_drop_controller_motion_new proto
gtk_drop_controller_motion_contains_pointer proto :ptr
gtk_drop_controller_motion_get_drop proto :ptr
gtk_drop_controller_motion_is_pointer proto :ptr

endif

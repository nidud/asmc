ifndef __GTK_EVENT_CONTROLLER_H__
define __GTK_EVENT_CONTROLLER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc
include gtk/gtkenums.inc

define GTK_TYPE_EVENT_CONTROLLER <gtk_event_controller_get_type ()>
GTK_EVENT_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER, GtkEventController))>
  endm
GTK_EVENT_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER, GtkEventControllerClass))>
  endm
GTK_IS_EVENT_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER))>
  endm
GTK_IS_EVENT_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER))>
  endm
GTK_EVENT_CONTROLLER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER, GtkEventControllerClass))>
  endm

gtk_event_controller_get_type proto
gtk_event_controller_get_widget proto :ptr
gtk_event_controller_reset proto :ptr
gtk_event_controller_get_propagation_phase proto :ptr
gtk_event_controller_set_propagation_phase proto :ptr, :GtkPropagationPhase
gtk_event_controller_get_propagation_limit proto :ptr
gtk_event_controller_set_propagation_limit proto :ptr, :GtkPropagationLimit
gtk_event_controller_get_name proto :ptr
gtk_event_controller_set_name proto :ptr, :ptr
gtk_event_controller_get_current_event proto :ptr
gtk_event_controller_get_current_event_time proto :ptr
gtk_event_controller_get_current_event_device proto :ptr
gtk_event_controller_get_current_event_state proto :ptr

endif

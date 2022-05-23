ifndef __GTK_EVENT_CONTROLLER_FOCUS_H__
define __GTK_EVENT_CONTROLLER_FOCUS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc
include gtk/gtkimcontext.inc

define GTK_TYPE_EVENT_CONTROLLER_FOCUS <gtk_event_controller_focus_get_type>
GTK_EVENT_CONTROLLER_FOCUS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER_FOCUS, GtkEventControllerFocus))>
  endm
GTK_EVENT_CONTROLLER_FOCUS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER_FOCUS, GtkEventControllerFocusClass))>
  endm
GTK_IS_EVENT_CONTROLLER_FOCUS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER_FOCUS))>
  endm
GTK_IS_EVENT_CONTROLLER_FOCUS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER_FOCUS))>
  endm
GTK_EVENT_CONTROLLER_FOCUS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER_FOCUS, GtkEventControllerFocusClass))>
  endm

;GtkEventControllerFocus typedef _GtkEventControllerFocus
;GtkEventControllerFocusClass typedef _GtkEventControllerFocusClass

gtk_event_controller_focus_get_type proto
gtk_event_controller_focus_new proto
gtk_event_controller_focus_contains_focus proto :ptr
gtk_event_controller_focus_is_focus proto :ptr

endif

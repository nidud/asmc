ifndef __GTK_EVENT_CONTROLLER_KEY_H__
define __GTK_EVENT_CONTROLLER_KEY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc
include gtk/gtkimcontext.inc

define GTK_TYPE_EVENT_CONTROLLER_KEY <gtk_event_controller_key_get_type ()>
GTK_EVENT_CONTROLLER_KEY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER_KEY, GtkEventControllerKey))>
  endm
GTK_EVENT_CONTROLLER_KEY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER_KEY, GtkEventControllerKeyClass))>
  endm
GTK_IS_EVENT_CONTROLLER_KEY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER_KEY))>
  endm
GTK_IS_EVENT_CONTROLLER_KEY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER_KEY))>
  endm
GTK_EVENT_CONTROLLER_KEY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER_KEY, GtkEventControllerKeyClass))>
  endm

gtk_event_controller_key_get_type proto
gtk_event_controller_key_new proto
gtk_event_controller_key_set_im_context proto :ptr, :ptr
gtk_event_controller_key_get_im_context proto :ptr
gtk_event_controller_key_forward proto :ptr, :ptr
gtk_event_controller_key_get_group proto :ptr

endif

ifndef __GTK_EVENT_CONTROLLER_SCROLL_H__
define __GTK_EVENT_CONTROLLER_SCROLL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkeventcontroller.inc

define GTK_TYPE_EVENT_CONTROLLER_SCROLL <gtk_event_controller_scroll_get_type ()>
GTK_EVENT_CONTROLLER_SCROLL macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER_SCROLL, GtkEventControllerScroll))>
  endm
GTK_EVENT_CONTROLLER_SCROLL_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER_SCROLL, GtkEventControllerScrollClass))>
  endm
GTK_IS_EVENT_CONTROLLER_SCROLL macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER_SCROLL))>
  endm
GTK_IS_EVENT_CONTROLLER_SCROLL_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER_SCROLL))>
  endm
GTK_EVENT_CONTROLLER_SCROLL_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER_SCROLL, GtkEventControllerScrollClass))>
  endm

.enum GtkEventControllerScrollFlags {
  GTK_EVENT_CONTROLLER_SCROLL_NONE       = 0,
  GTK_EVENT_CONTROLLER_SCROLL_VERTICAL   = 1 shl 0,
  GTK_EVENT_CONTROLLER_SCROLL_HORIZONTAL = 1 shl 1,
  GTK_EVENT_CONTROLLER_SCROLL_DISCRETE   = 1 shl 2,
  GTK_EVENT_CONTROLLER_SCROLL_KINETIC    = 1 shl 3,
  GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES  = (GTK_EVENT_CONTROLLER_SCROLL_VERTICAL or GTK_EVENT_CONTROLLER_SCROLL_HORIZONTAL),
}

gtk_event_controller_scroll_get_type proto
gtk_event_controller_scroll_new proto :GtkEventControllerScrollFlags
gtk_event_controller_scroll_set_flags proto :ptr, :GtkEventControllerScrollFlags
gtk_event_controller_scroll_get_flags proto :ptr

endif

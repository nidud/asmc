ifndef __GTK_EVENT_CONTROLLER_LEGACY_H__
define __GTK_EVENT_CONTROLLER_LEGACY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeventcontroller.inc

define GTK_TYPE_EVENT_CONTROLLER_LEGACY <gtk_event_controller_legacy_get_type ()>
GTK_EVENT_CONTROLLER_LEGACY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_EVENT_CONTROLLER_LEGACY, GtkEventControllerLegacy))>
  endm
GTK_EVENT_CONTROLLER_LEGACY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_EVENT_CONTROLLER_LEGACY, GtkEventControllerLegacyClass))>
  endm
GTK_IS_EVENT_CONTROLLER_LEGACY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_EVENT_CONTROLLER_LEGACY))>
  endm
GTK_IS_EVENT_CONTROLLER_LEGACY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_EVENT_CONTROLLER_LEGACY))>
  endm
GTK_EVENT_CONTROLLER_LEGACY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_EVENT_CONTROLLER_LEGACY, GtkEventControllerLegacyClass))>
  endm

;GtkEventControllerLegacy typedef _GtkEventControllerLegacy
;GtkEventControllerLegacyClass typedef _GtkEventControllerLegacyClass

gtk_event_controller_legacy_get_type proto
gtk_event_controller_legacy_new proto

endif

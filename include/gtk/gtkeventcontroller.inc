ifndef __GTK_EVENT_CONTROLLER_H__
__GTK_EVENT_CONTROLLER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_EVENT_CONTROLLER equ <gtk_event_controller_get_type>
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


;GType
gtk_event_controller_get_type proto __cdecl

;GtkWidget
gtk_event_controller_get_widget proto __cdecl \
	    controller: ptr GtkEventController


;gboolean
gtk_event_controller_handle_event proto __cdecl \
	    controller: ptr GtkEventController,
		 event: ptr GdkEvent

;void
gtk_event_controller_reset proto __cdecl \
	    controller: ptr GtkEventController


;GtkPropagationPhase
gtk_event_controller_get_propagation_phase proto __cdecl \
	    controller: ptr GtkEventController


;void
gtk_event_controller_set_propagation_phase proto __cdecl \
	    controller: ptr GtkEventController,
		 phase: GtkPropagationPhase

G_END_DECLS

endif

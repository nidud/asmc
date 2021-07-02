ifndef __GTK_POPOVER_H__
__GTK_POPOVER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

GTK_TYPE_POPOVER equ <gtk_popover_get_type>
GTK_POPOVER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_POPOVER, GtkPopover))>
	endm
GTK_POPOVER_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST ((c), GTK_TYPE_POPOVER, GtkPopoverClass))>
	endm
GTK_IS_POPOVER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_POPOVER))>
	endm
GTK_IS_POPOVER_CLASS macro o
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((o), GTK_TYPE_POPOVER))>
	endm
GTK_POPOVER_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_POPOVER, GtkPopoverClass))>
	endm

GtkPopover		STRUC
parent_instance		GtkBin <>
priv			ptr_t ?
GtkPopover		ENDS

GtkPopoverClass		STRUC
parent_class		GtkBinClass <>
closed			proc :ptr GtkPopover
reserved		gpointer 10 dup(?)
GtkPopoverClass		ENDS

;GType
gtk_popover_get_type proto __cdecl

;GtkWidget
gtk_popover_new proto __cdecl \
	   relative_to: ptr GtkWidget


;GtkWidget
gtk_popover_new_from_model proto __cdecl \
	   relative_to: ptr GtkWidget,
		 model: ptr GMenuModel


;void
gtk_popover_set_relative_to proto __cdecl \
	       popover: ptr GtkPopover,
	   relative_to: ptr GtkWidget

;GtkWidget
gtk_popover_get_relative_to proto __cdecl \
	       popover: ptr GtkPopover


;void
gtk_popover_set_pointing_to proto __cdecl \
	       popover: ptr GtkPopover,
		  rect: ptr GdkRectangle

;gboolean
gtk_popover_get_pointing_to proto __cdecl \
	       popover: ptr GtkPopover,
		  rect: ptr GdkRectangle

;void
gtk_popover_set_position proto __cdecl \
	       popover: ptr GtkPopover,
	      position: GtkPositionType

;GtkPositionType
gtk_popover_get_position proto __cdecl \
	       popover: ptr GtkPopover


;void
gtk_popover_set_modal proto __cdecl \
	       popover: ptr GtkPopover,
		 modal: gboolean

;gboolean
gtk_popover_get_modal proto __cdecl \
	       popover: ptr GtkPopover


;void
gtk_popover_bind_model proto __cdecl \
	       popover: ptr GtkPopover,
		 model: ptr GMenuModel,
      action_namespace: ptr gchar


;void
gtk_popover_set_transitions_enabled proto __cdecl \
	       popover: ptr GtkPopover,
   transitions_enabled: gboolean

;gboolean
gtk_popover_get_transitions_enabled proto __cdecl \
	       popover: ptr GtkPopover


;void
gtk_popover_set_default_widget proto __cdecl \
	       popover: ptr GtkPopover,
		widget: ptr GtkWidget

;GtkWidget
gtk_popover_get_default_widget proto __cdecl \
	       popover: ptr GtkPopover

G_END_DECLS

endif

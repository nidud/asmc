ifndef __GTK_SWITCH_H__
__GTK_SWITCH_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_SWITCH equ <gtk_switch_get_type>
GTK_SWITCH macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SWITCH, GtkSwitch))>
	endm
GTK_IS_SWITCH macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SWITCH))>
	endm
GTK_SWITCH_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SWITCH, GtkSwitchClass))>
	endm
GTK_IS_SWITCH_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SWITCH))>
	endm
GTK_SWITCH_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SWITCH, GtkSwitchClass))>
	endm

StkSwitch		STRUC
parent_instance		GtkWidget <>
priv			ptr_t ?
StkSwitch		ENDS

GtkSwitchClass		STRUC
parent_class		GtkWidgetClass <>
activate		proc :ptr GtkSwitch
state_set		proc :ptr GtkSwitch, :gboolean
_switch_padding_1	proc
_switch_padding_2	proc
_switch_padding_3	proc
_switch_padding_4	proc
_switch_padding_5	proc
GtkSwitchClass		ENDS

;GType
gtk_switch_get_type proto __cdecl

;GtkWidget
gtk_switch_new proto __cdecl

;void
gtk_switch_set_active proto __cdecl \
		    sw: ptr GtkSwitch,
	     is_active: gboolean

;gboolean
gtk_switch_get_active proto __cdecl \
		    sw: ptr GtkSwitch

;void
gtk_switch_set_state proto __cdecl \
		    sw: ptr GtkSwitch,
		 state: gboolean

;gboolean
gtk_switch_get_state proto __cdecl \
		    sw: ptr GtkSwitch

G_END_DECLS

endif

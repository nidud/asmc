ifndef __GTK_RADIO_BUTTON_H__
__GTK_RADIO_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcheckbutton.inc

G_BEGIN_DECLS

GTK_TYPE_RADIO_BUTTON equ <gtk_radio_button_get_type>
GTK_RADIO_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RADIO_BUTTON, GtkRadioButton))>
	endm
GTK_RADIO_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RADIO_BUTTON, GtkRadioButtonClass))>
	endm
GTK_IS_RADIO_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RADIO_BUTTON))>
	endm
GTK_IS_RADIO_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RADIO_BUTTON))>
	endm
GTK_RADIO_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RADIO_BUTTON, GtkRadioButtonClass))>
	endm


GtkRadioButton		STRUC
check_button		GtkCheckButton <>
priv			ptr_t ?
GtkRadioButton		ENDS

GtkRadioButtonClass	STRUC
parent_class		GtkCheckButtonClass <>
group_changed		proc :ptr GtkRadioButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRadioButtonClass	ENDS

;GType
gtk_radio_button_get_type proto __cdecl

;GtkWidget*
gtk_radio_button_new proto __cdecl \
		_group: ptr GSList

;GtkWidget*
gtk_radio_button_new_from_widget proto __cdecl \
    radio_group_member: ptr GtkRadioButton

;GtkWidget*
gtk_radio_button_new_with_label proto __cdecl \
		_group: ptr GSList,
		_label: ptr gchar

;GtkWidget*
gtk_radio_button_new_with_label_from_widget proto __cdecl \
    radio_group_member: ptr GtkRadioButton,
		_label: ptr gchar

;GtkWidget*
gtk_radio_button_new_with_mnemonic proto __cdecl \
		_group: ptr GSList,
		_label: ptr gchar

;GtkWidget*
gtk_radio_button_new_with_mnemonic_from_widget proto __cdecl \
    radio_group_member: ptr GtkRadioButton,
		_label: ptr gchar

;GSList*
gtk_radio_button_get_group proto __cdecl \
	  radio_button: ptr GtkRadioButton

;void
gtk_radio_button_set_group proto __cdecl \
	  radio_button: ptr GtkRadioButton,
		_group: ptr GSList

;void
gtk_radio_button_join_group proto __cdecl \
	  radio_button: ptr GtkRadioButton,
	  group_source: ptr GtkRadioButton

G_END_DECLS

endif

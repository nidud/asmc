ifndef __GTK_RADIO_TOOL_BUTTON_H__
__GTK_RADIO_TOOL_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktoggletoolbutton.inc

G_BEGIN_DECLS

GTK_TYPE_RADIO_TOOL_BUTTON equ <gtk_radio_tool_button_get_type>
GTK_RADIO_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RADIO_TOOL_BUTTON, GtkRadioToolButton))>
	endm
GTK_RADIO_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RADIO_TOOL_BUTTON, GtkRadioToolButtonClass))>
	endm
GTK_IS_RADIO_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RADIO_TOOL_BUTTON))>
	endm
GTK_IS_RADIO_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RADIO_TOOL_BUTTON))>
	endm
GTK_RADIO_TOOL_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_RADIO_TOOL_BUTTON, GtkRadioToolButtonClass))>
	endm

GtkRadioToolButton	STRUC
parent			GtkToggleToolButton <>
GtkRadioToolButton	ENDS

GtkRadioToolButtonClass STRUC
parent_class		GtkToggleToolButtonClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRadioToolButtonClass ENDS

;GType
gtk_radio_tool_button_get_type proto __cdecl

;GtkToolItem
gtk_radio_tool_button_new proto __cdecl \
		_group: ptr GSList

;GtkToolItem
gtk_radio_tool_button_new_from_stock proto __cdecl \
		_group: ptr GSList,
	      stock_id: ptr gchar

;GtkToolItem
gtk_radio_tool_button_new_from_widget proto __cdecl \
		_group: ptr GtkRadioToolButton

;GtkToolItem
gtk_radio_tool_button_new_with_stock_from_widget proto __cdecl \
		_group: ptr GtkRadioToolButton,
	      stock_id: ptr gchar

;GSList
gtk_radio_tool_button_get_group proto __cdecl \
		button: ptr GtkRadioToolButton

;void
gtk_radio_tool_button_set_group proto __cdecl \
		button: ptr GtkRadioToolButton,
		_group: ptr GSList


G_END_DECLS

endif

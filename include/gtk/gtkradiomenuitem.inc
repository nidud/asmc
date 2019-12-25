ifndef __GTK_RADIO_MENU_ITEM_H__
__GTK_RADIO_MENU_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcheckmenuitem.inc

G_BEGIN_DECLS

GTK_TYPE_RADIO_MENU_ITEM equ <gtk_radio_menu_item_get_type>
GTK_RADIO_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RADIO_MENU_ITEM, GtkRadioMenuItem))>
	endm
GTK_RADIO_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RADIO_MENU_ITEM, GtkRadioMenuItemClass))>
	endm
GTK_IS_RADIO_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RADIO_MENU_ITEM))>
	endm
GTK_IS_RADIO_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RADIO_MENU_ITEM))>
	endm
GTK_RADIO_MENU_ITEM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RADIO_MENU_ITEM, GtkRadioMenuItemClass))>
	endm


GtkRadioMenuItem	STRUC
check_menu_item		GtkCheckMenuItem <>
priv			ptr_t ?
GtkRadioMenuItem	ENDS

GtkRadioMenuItemClass	STRUC
parent_class		GtkCheckMenuItemClass <>
group_changed		proc :ptr GtkRadioMenuItem
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRadioMenuItemClass	ENDS


;GType
gtk_radio_menu_item_get_type proto __cdecl

;GtkWidget*
gtk_radio_menu_item_new proto __cdecl \
		_group: ptr GSList

;GtkWidget*
gtk_radio_menu_item_new_with_label proto __cdecl \
		_group: ptr GSList,
		_label: ptr gchar

;GtkWidget*
gtk_radio_menu_item_new_with_mnemonic proto __cdecl \
		_group: ptr GSList,
		_label: ptr gchar

;GtkWidget*
gtk_radio_menu_item_new_from_widget proto __cdecl \
		_group: ptr GtkRadioMenuItem

;GtkWidget
gtk_radio_menu_item_new_with_mnemonic_from_widget proto __cdecl \
		_group: ptr GtkRadioMenuItem,
		_label: ptr gchar

;GtkWidget
gtk_radio_menu_item_new_with_label_from_widget proto __cdecl \
		_group: ptr GtkRadioMenuItem,
		_label: ptr gchar

;GSList*
gtk_radio_menu_item_get_group proto __cdecl \
       radio_menu_item: ptr GtkRadioMenuItem

;void
gtk_radio_menu_item_set_group proto __cdecl \
       radio_menu_item: ptr GtkRadioMenuItem,
		_group: ptr GSList


;void
gtk_radio_menu_item_join_group proto __cdecl \
       radio_menu_item: ptr GtkRadioMenuItem,
	  group_source: ptr GtkRadioMenuItem


G_END_DECLS

endif

ifndef __GTK_SEPARATOR_MENU_ITEM_H__
__GTK_SEPARATOR_MENU_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmenuitem.inc

G_BEGIN_DECLS

GTK_TYPE_SEPARATOR_MENU_ITEM equ <gtk_separator_menu_item_get_type>
GTK_SEPARATOR_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEPARATOR_MENU_ITEM, GtkSeparatorMenuItem))>
	endm
GTK_SEPARATOR_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SEPARATOR_MENU_ITEM, GtkSeparatorMenuItemClass))>
	endm
GTK_IS_SEPARATOR_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEPARATOR_MENU_ITEM))>
	endm
GTK_IS_SEPARATOR_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SEPARATOR_MENU_ITEM))>
	endm
GTK_SEPARATOR_MENU_ITEM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SEPARATOR_MENU_ITEM, GtkSeparatorMenuItemClass))>
	endm


GtkSeparatorMenuItem	STRUC
menu_item		GtkMenuItem <>
GtkSeparatorMenuItem	ENDS

GtkSeparatorMenuItemClass STRUC
parent_class		GtkMenuItemClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSeparatorMenuItemClass ENDS

;GType
gtk_separator_menu_item_get_type proto __cdecl
;GtkWidget*
gtk_separator_menu_item_new proto __cdecl

G_END_DECLS

endif

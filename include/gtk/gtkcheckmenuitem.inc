ifndef __GTK_CHECK_MENU_ITEM_H__
__GTK_CHECK_MENU_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmenuitem.inc

G_BEGIN_DECLS

GTK_TYPE_CHECK_MENU_ITEM equ <gtk_check_menu_item_get_type>
GTK_CHECK_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CHECK_MENU_ITEM, GtkCheckMenuItem))>
	endm
GTK_CHECK_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CHECK_MENU_ITEM, GtkCheckMenuItemClass))>
	endm
GTK_IS_CHECK_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CHECK_MENU_ITEM))>
	endm
GTK_IS_CHECK_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CHECK_MENU_ITEM))>
	endm
GTK_CHECK_MENU_ITEM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CHECK_MENU_ITEM, GtkCheckMenuItemClass))>
	endm


GtkCheckMenuItem	STRUC
menu_item		GtkMenuItem <>
priv			ptr_t ?
GtkCheckMenuItem	ENDS

GtkCheckMenuItemClass	STRUC
parent_class		GtkMenuItemClass <>
toggled			proc :ptr GtkCheckMenuItem
draw_indicator		proc :ptr GtkCheckMenuItem, :ptr cairo_t
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCheckMenuItemClass	ENDS


;GType
gtk_check_menu_item_get_type proto __cdecl

;GtkWidget*
gtk_check_menu_item_new proto __cdecl
;GtkWidget*
gtk_check_menu_item_new_with_label proto __cdecl \
		_label: ptr gchar

;GtkWidget*
gtk_check_menu_item_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
gtk_check_menu_item_set_active proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem,
	     is_active: gboolean

;gboolean
gtk_check_menu_item_get_active proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem

;void
gtk_check_menu_item_toggled proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem

;void
gtk_check_menu_item_set_inconsistent proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem,
	       setting: gboolean

;gboolean
gtk_check_menu_item_get_inconsistent proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem

;void
gtk_check_menu_item_set_draw_as_radio proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem,
	 draw_as_radio: gboolean

;gboolean
gtk_check_menu_item_get_draw_as_radio proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem

;void
_gtk_check_menu_item_set_active proto __cdecl \
       check_menu_item: ptr GtkCheckMenuItem,
	     is_active: gboolean

G_END_DECLS

endif

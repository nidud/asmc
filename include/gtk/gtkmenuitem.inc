ifndef __GTK_MENU_ITEM_H__
__GTK_MENU_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc


G_BEGIN_DECLS

GTK_TYPE_MENU_ITEM equ <gtk_menu_item_get_type>
GTK_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU_ITEM, GtkMenuItem))>
	endm
GTK_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MENU_ITEM, GtkMenuItemClass))>
	endm
GTK_IS_MENU_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU_ITEM))>
	endm
GTK_IS_MENU_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MENU_ITEM))>
	endm
GTK_MENU_ITEM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MENU_ITEM, GtkMenuItemClass))>
	endm


GtkMenuItem		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkMenuItem		ENDS

GtkMenuItemClass	STRUC
parent_class		GtkBinClass <>
hide_on_activate	guint ? ; : 1
activate		proc :ptr GtkMenuItem
activate_item		proc :ptr GtkMenuItem
toggle_size_request	proc :ptr GtkMenuItem, :ptr gint
toggle_size_allocate	proc :ptr GtkMenuItem, :gint
set_label		proc :ptr GtkMenuItem, :ptr gchar
get_label		proc :ptr GtkMenuItem
select			proc :ptr GtkMenuItem
deselect		proc :ptr GtkMenuItem
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuItemClass	ENDS


;GType
gtk_menu_item_get_type proto __cdecl

;GtkWidget*
gtk_menu_item_new proto __cdecl
;GtkWidget*
gtk_menu_item_new_with_label proto __cdecl \
		_label: ptr gchar

;GtkWidget*
gtk_menu_item_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
gtk_menu_item_set_submenu proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	       submenu: ptr GtkWidget

;GtkWidget*
gtk_menu_item_get_submenu proto __cdecl \
	     menu_item: ptr GtkMenuItem

;void
gtk_menu_item_select proto __cdecl \
	     menu_item: ptr GtkMenuItem

;void
gtk_menu_item_deselect proto __cdecl \
	     menu_item: ptr GtkMenuItem

;void
gtk_menu_item_activate proto __cdecl \
	     menu_item: ptr GtkMenuItem

;void
gtk_menu_item_toggle_size_request proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	   requisition: ptr gint

;void
gtk_menu_item_toggle_size_allocate proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	    allocation: gint

;void
gtk_menu_item_set_right_justified proto __cdecl \
	     menu_item: ptr GtkMenuItem,
       right_justified: gboolean

;gboolean
gtk_menu_item_get_right_justified proto __cdecl \
	     menu_item: ptr GtkMenuItem

;void
gtk_menu_item_set_accel_path proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	    accel_path: ptr gchar

;const
gtk_menu_item_get_accel_path proto __cdecl \
	     menu_item: ptr GtkMenuItem


;void
gtk_menu_item_set_label proto __cdecl \
	     menu_item: ptr GtkMenuItem,
		_label: ptr gchar

;const
gtk_menu_item_get_label proto __cdecl \
	     menu_item: ptr GtkMenuItem


;void
gtk_menu_item_set_use_underline proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	       setting: gboolean

;gboolean
gtk_menu_item_get_use_underline proto __cdecl \
	     menu_item: ptr GtkMenuItem


;void
gtk_menu_item_set_reserve_indicator proto __cdecl \
	     menu_item: ptr GtkMenuItem,
	       reserve: gboolean

;gboolean
gtk_menu_item_get_reserve_indicator proto __cdecl \
	     menu_item: ptr GtkMenuItem

G_END_DECLS

endif

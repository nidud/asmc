ifndef __GTK_POPOVER_MENU_H__
__GTK_POPOVER_MENU_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpopover.inc

G_BEGIN_DECLS

GTK_TYPE_POPOVER_MENU equ <gtk_popover_menu_get_type>
GTK_POPOVER_MENU macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_POPOVER_MENU, GtkPopoverMenu))>
	endm
GTK_POPOVER_MENU_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST ((c), GTK_TYPE_POPOVER_MENU, GtkPopoverMenuClass))>
	endm
GTK_IS_POPOVER_MENU macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_POPOVER_MENU))>
	endm
GTK_IS_POPOVER_MENU_CLASS macro o
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((o), GTK_TYPE_POPOVER_MENU))>
	endm
GTK_POPOVER_MENU_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_POPOVER_MENU, GtkPopoverMenuClass))>
	endm

GtkPopoverMenuClass	STRUC
parent_class		GtkPopoverClass <>
reserved		gpointer 10 dup(?)
GtkPopoverMenuClass	ENDS

;GType
gtk_popover_menu_get_type proto __cdecl

;GtkWidget
gtk_popover_menu_new proto __cdecl

;void
gtk_popover_menu_open_submenu proto __cdecl \
	       popover: ptr GtkPopoverMenu,
		  name: ptr gchar

G_END_DECLS

endif

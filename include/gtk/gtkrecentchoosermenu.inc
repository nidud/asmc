ifndef __GTK_RECENT_CHOOSER_MENU_H__
__GTK_RECENT_CHOOSER_MENU_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmenu.inc
include gtk/gtkrecentchooser.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_CHOOSER_MENU equ <gtk_recent_chooser_menu_get_type>
GTK_RECENT_CHOOSER_MENU macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_CHOOSER_MENU, GtkRecentChooserMenu))>
	endm
GTK_IS_RECENT_CHOOSER_MENU macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_CHOOSER_MENU))>
	endm
GTK_RECENT_CHOOSER_MENU_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RECENT_CHOOSER_MENU, GtkRecentChooserMenuClass))>
	endm
GTK_IS_RECENT_CHOOSER_MENU_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RECENT_CHOOSER_MENU))>
	endm
GTK_RECENT_CHOOSER_MENU_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RECENT_CHOOSER_MENU, GtkRecentChooserMenuClass))>
	endm

GtkRecentChooserMenu	STRUC
parent_instance		GtkMenu <>
priv			ptr_t ?
GtkRecentChooserMenu	ENDS

GtkRecentChooserMenuClass STRUC
parent_class		GtkMenuClass <>
gtk_recent1		proc
gtk_recent2		proc
gtk_recent3		proc
gtk_recent4		proc
GtkRecentChooserMenuClass ENDS

;GType
gtk_recent_chooser_menu_get_type proto __cdecl

;GtkWidget
gtk_recent_chooser_menu_new proto __cdecl
;GtkWidget
gtk_recent_chooser_menu_new_for_manager proto __cdecl \
	       manager: ptr GtkRecentManager


;gboolean
gtk_recent_chooser_menu_get_show_numbers proto __cdecl \
		  menu: ptr GtkRecentChooserMenu

;void
gtk_recent_chooser_menu_set_show_numbers proto __cdecl \
		  menu: ptr GtkRecentChooserMenu,
	  show_numbers: gboolean


G_END_DECLS

endif

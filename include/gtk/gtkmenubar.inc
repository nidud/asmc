ifndef __GTK_MENU_BAR_H__
__GTK_MENU_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmenushell.inc

G_BEGIN_DECLS

GTK_TYPE_MENU_BAR equ <gtk_menu_bar_get_type>
GTK_MENU_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU_BAR, GtkMenuBar))>
	endm
GTK_MENU_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MENU_BAR, GtkMenuBarClass))>
	endm
GTK_IS_MENU_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU_BAR))>
	endm
GTK_IS_MENU_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MENU_BAR))>
	endm
GTK_MENU_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MENU_BAR, GtkMenuBarClass))>
	endm

GtkMenuBar		STRUC
menu_shell		GtkMenuShell <>
priv			ptr_t ?
GtkMenuBar		ENDS

GtkMenuBarClass		STRUC
parent_class		GtkMenuShellClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuBarClass		ENDS


;GType
gtk_menu_bar_get_type proto __cdecl
;GtkWidget*
gtk_menu_bar_new proto __cdecl
;GtkWidget*
gtk_menu_bar_new_from_model proto __cdecl \
		 model: ptr GMenuModel


;GtkPackDirection
gtk_menu_bar_get_pack_direction proto __cdecl \
	       menubar: ptr GtkMenuBar

;void
gtk_menu_bar_set_pack_direction proto __cdecl \
	       menubar: ptr GtkMenuBar,
	      pack_dir: GtkPackDirection

;GtkPackDirection
gtk_menu_bar_get_child_pack_direction proto __cdecl \
	       menubar: ptr GtkMenuBar

;void
gtk_menu_bar_set_child_pack_direction proto __cdecl \
	       menubar: ptr GtkMenuBar,
	child_pack_dir: GtkPackDirection


;void
_gtk_menu_bar_cycle_focus proto __cdecl \
	       menubar: ptr GtkMenuBar,
		   dir: GtkDirectionType

;GList*
_gtk_menu_bar_get_viewable_menu_bars proto __cdecl \
		window: ptr GtkWindow

G_END_DECLS

endif

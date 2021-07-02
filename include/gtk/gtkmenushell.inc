ifndef __GTK_MENU_SHELL_H__
__GTK_MENU_SHELL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_MENU_SHELL equ <gtk_menu_shell_get_type>
GTK_MENU_SHELL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU_SHELL, GtkMenuShell))>
	endm
GTK_MENU_SHELL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MENU_SHELL, GtkMenuShellClass))>
	endm
GTK_IS_MENU_SHELL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU_SHELL))>
	endm
GTK_IS_MENU_SHELL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MENU_SHELL))>
	endm
GTK_MENU_SHELL_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MENU_SHELL, GtkMenuShellClass))>
	endm

GtkMenuShell		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkMenuShell		ENDS

GtkMenuShellClass	STRUC
parent_class		GtkContainerClass <>
submenu_placement	guint ? ; : 1
deactivate		proc :ptr GtkMenuShell
selection_done		proc :ptr GtkMenuShell
move_current		proc :ptr GtkMenuShell, :GtkMenuDirectionType
activate_current	proc :ptr GtkMenuShell, :gboolean
cancel			proc :ptr GtkMenuShell
select_item		proc :ptr GtkMenuShell, :ptr_t
insert			proc :ptr GtkMenuShell, :ptr_t, :gint
get_popup_delay		proc :ptr GtkMenuShell, :gint
move_selected		proc :ptr GtkMenuShell, :gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuShellClass	ENDS

;GType
gtk_menu_shell_get_type proto __cdecl

;void
gtk_menu_shell_append proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
		 child: ptr GtkWidget

;void
gtk_menu_shell_prepend proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
		 child: ptr GtkWidget

;void
gtk_menu_shell_insert proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
		 child: ptr GtkWidget,
	      position: gint

;void
gtk_menu_shell_deactivate proto __cdecl \
	    menu_shell: ptr GtkMenuShell

;void
gtk_menu_shell_select_item proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
	     menu_item: ptr GtkWidget

;void
gtk_menu_shell_deselect proto __cdecl \
	    menu_shell: ptr GtkMenuShell

;void
gtk_menu_shell_activate_item proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
	     menu_item: ptr GtkWidget,
      force_deactivate: gboolean

;void
gtk_menu_shell_select_first proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
      search_sensitive: gboolean

;void
gtk_menu_shell_cancel proto __cdecl \
	    menu_shell: ptr GtkMenuShell

;gboolean
gtk_menu_shell_get_take_focus proto __cdecl \
	    menu_shell: ptr GtkMenuShell

;void
gtk_menu_shell_set_take_focus proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
	    take_focus: gboolean


;GtkWidget
gtk_menu_shell_get_selected_item proto __cdecl \
	    menu_shell: ptr GtkMenuShell

;GtkWidget
gtk_menu_shell_get_parent_shell proto __cdecl \
	    menu_shell: ptr GtkMenuShell


;void
gtk_menu_shell_bind_model proto __cdecl \
	    menu_shell: ptr GtkMenuShell,
		 model: ptr GMenuModel,
      action_namespace: ptr gchar,
       with_separators: gboolean


G_END_DECLS

endif

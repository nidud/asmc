ifndef __GTK_POPOVER_MENU_BAR_H__
define __GTK_POPOVER_MENU_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpopover.inc

define	GTK_TYPE_POPOVER_MENU_BAR  <gtk_popover_menu_bar_get_type>
GTK_POPOVER_MENU_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_POPOVER_MENU_BAR, GtkPopoverMenuBar))>
  endm
GTK_IS_POPOVER_MENU_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_POPOVER_MENU_BAR))>
  endm

;GtkPopoverMenuBar	 typedef _GtkPopoverMenuBar

gtk_popover_menu_bar_get_type proto
gtk_popover_menu_bar_new_from_model proto :ptr
gtk_popover_menu_bar_set_menu_model proto :ptr, :ptr
gtk_popover_menu_bar_get_menu_model proto :ptr
gtk_popover_menu_bar_add_child proto :ptr, :ptr, :ptr
gtk_popover_menu_bar_remove_child proto :ptr, :ptr

endif

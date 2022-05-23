ifndef __GTK_POPOVER_MENU_H__
define __GTK_POPOVER_MENU_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpopover.inc

define GTK_TYPE_POPOVER_MENU <gtk_popover_menu_get_type>
GTK_POPOVER_MENU macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_POPOVER_MENU, GtkPopoverMenu))>
  endm
GTK_IS_POPOVER_MENU macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_POPOVER_MENU))>
  endm

;GtkPopoverMenu          typedef _GtkPopoverMenu

gtk_popover_menu_get_type proto
gtk_popover_menu_new_from_model proto :ptr

.enum GtkPopoverMenuFlags {
  GTK_POPOVER_MENU_NESTED = 1 shl 0
}

gtk_popover_menu_new_from_model_full proto :ptr, :GtkPopoverMenuFlags
gtk_popover_menu_set_menu_model proto :ptr, :ptr
gtk_popover_menu_get_menu_model proto :ptr
gtk_popover_menu_add_child proto :ptr, :ptr, :ptr
gtk_popover_menu_remove_child proto :ptr, :ptr

endif

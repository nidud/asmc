ifndef __GTK_MENU_BUTTON_H__
define __GTK_MENU_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktogglebutton.inc
include gtk/gtkpopover.inc

define GTK_TYPE_MENU_BUTTON <gtk_menu_button_get_type ()>
GTK_MENU_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU_BUTTON, GtkMenuButton))>
  endm
GTK_IS_MENU_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU_BUTTON))>
  endm

;GtkMenuButton           typedef _GtkMenuButton

CALLBACK(GtkMenuButtonCreatePopupFunc, :ptr, :gpointer)

gtk_menu_button_get_type proto
gtk_menu_button_new proto

gtk_menu_button_set_popover proto :ptr, :ptr
gtk_menu_button_get_popover proto :ptr

gtk_menu_button_set_direction proto :ptr, :GtkArrowType
gtk_menu_button_get_direction proto :ptr

gtk_menu_button_set_menu_model proto :ptr, :ptr
gtk_menu_button_get_menu_model proto :ptr

gtk_menu_button_set_icon_name proto :ptr, :ptr
gtk_menu_button_get_icon_name proto :ptr

gtk_menu_button_set_always_show_arrow proto :ptr, :gboolean
gtk_menu_button_get_always_show_arrow proto :ptr

gtk_menu_button_set_label proto :ptr, :ptr
gtk_menu_button_get_label proto :ptr

gtk_menu_button_set_use_underline proto :ptr, :gboolean
gtk_menu_button_get_use_underline proto :ptr

gtk_menu_button_set_has_frame proto :ptr, :gboolean
gtk_menu_button_get_has_frame proto :ptr

gtk_menu_button_popup proto :ptr
gtk_menu_button_popdown proto :ptr

gtk_menu_button_set_create_popup_func proto :ptr, :GtkMenuButtonCreatePopupFunc, :gpointer, :GDestroyNotify

gtk_menu_button_set_primary proto :ptr, :gboolean
gtk_menu_button_get_primary proto :ptr

gtk_menu_button_set_child proto :ptr, :ptr
gtk_menu_button_get_child proto :ptr

endif

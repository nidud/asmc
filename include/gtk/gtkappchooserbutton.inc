ifndef __GTK_APP_CHOOSER_BUTTON_H__
define __GTK_APP_CHOOSER_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gio/gio.inc

define GTK_TYPE_APP_CHOOSER_BUTTON <gtk_app_chooser_button_get_type ()>
GTK_APP_CHOOSER_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_BUTTON, GtkAppChooserButton))>
  endm
GTK_IS_APP_CHOOSER_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_BUTTON))>
  endm

;GtkAppChooserButton     typedef _GtkAppChooserButton

gtk_app_chooser_button_get_type proto

gtk_app_chooser_button_new proto :ptr

gtk_app_chooser_button_append_separator proto :ptr
gtk_app_chooser_button_append_custom_item proto :ptr, :ptr, :ptr, :ptr
gtk_app_chooser_button_set_active_custom_item proto :ptr, :ptr

gtk_app_chooser_button_set_show_dialog_item proto :ptr, :gboolean
gtk_app_chooser_button_get_show_dialog_item proto :ptr
gtk_app_chooser_button_set_heading proto :ptr, :ptr
gtk_app_chooser_button_get_heading proto :ptr
gtk_app_chooser_button_set_show_default_item proto :ptr, :gboolean
gtk_app_chooser_button_get_show_default_item proto :ptr

gtk_app_chooser_button_get_modal proto :ptr
gtk_app_chooser_button_set_modal proto :ptr, :gboolean

endif

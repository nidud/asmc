ifndef __GTK_APP_CHOOSER_DIALOG_H__
define __GTK_APP_CHOOSER_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gio/gio.inc

define GTK_TYPE_APP_CHOOSER_DIALOG <gtk_app_chooser_dialog_get_type ()>
GTK_APP_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_DIALOG, GtkAppChooserDialog))>
  endm
GTK_IS_APP_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_DIALOG))>
  endm

gtk_app_chooser_dialog_get_type proto

gtk_app_chooser_dialog_new proto :ptr, :GtkDialogFlags, :ptr
gtk_app_chooser_dialog_new_for_content_type proto :ptr, :GtkDialogFlags, :ptr

gtk_app_chooser_dialog_get_widget proto :ptr
gtk_app_chooser_dialog_set_heading proto :ptr, :ptr
gtk_app_chooser_dialog_get_heading proto :ptr

endif

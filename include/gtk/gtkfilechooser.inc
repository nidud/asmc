ifndef __GTK_FILE_CHOOSER_H__
define __GTK_FILE_CHOOSER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilefilter.inc
include gtk/gtkwidget.inc

define GTK_TYPE_FILE_CHOOSER <gtk_file_chooser_get_type ()>
GTK_FILE_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER, GtkFileChooser))>
  endm
GTK_IS_FILE_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER))>
  endm

;GtkFileChooser          typedef _GtkFileChooser

.enum GtkFileChooserAction {
  GTK_FILE_CHOOSER_ACTION_OPEN,
  GTK_FILE_CHOOSER_ACTION_SAVE,
  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER
}

gtk_file_chooser_get_type proto

define GTK_FILE_CHOOSER_ERROR <gtk_file_chooser_error_quark ()>

.enum GtkFileChooserError {
  GTK_FILE_CHOOSER_ERROR_NONEXISTENT,
  GTK_FILE_CHOOSER_ERROR_BAD_FILENAME,
  GTK_FILE_CHOOSER_ERROR_ALREADY_EXISTS,
  GTK_FILE_CHOOSER_ERROR_INCOMPLETE_HOSTNAME
}

gtk_file_chooser_error_quark proto
gtk_file_chooser_set_action proto :ptr, :GtkFileChooserAction
gtk_file_chooser_get_action proto :ptr
gtk_file_chooser_set_select_multiple proto :ptr, :gboolean
gtk_file_chooser_get_select_multiple proto :ptr
gtk_file_chooser_set_create_folders proto :ptr, :gboolean
gtk_file_chooser_get_create_folders proto :ptr
gtk_file_chooser_set_current_name proto :ptr, :ptr
gtk_file_chooser_get_current_name proto :ptr
gtk_file_chooser_get_file proto :ptr
gtk_file_chooser_set_file proto :ptr, :ptr, :ptr
gtk_file_chooser_get_files proto :ptr
gtk_file_chooser_set_current_folder proto :ptr, :ptr, :ptr
gtk_file_chooser_get_current_folder proto :ptr
gtk_file_chooser_add_filter proto :ptr, :ptr
gtk_file_chooser_remove_filter proto :ptr, :ptr
gtk_file_chooser_get_filters proto :ptr
gtk_file_chooser_set_filter proto :ptr, :ptr
gtk_file_chooser_get_filter proto :ptr
gtk_file_chooser_add_shortcut_folder proto :ptr, :ptr, :ptr
gtk_file_chooser_remove_shortcut_folder proto :ptr, :ptr, :ptr
gtk_file_chooser_get_shortcut_folders proto :ptr
gtk_file_chooser_add_choice proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_file_chooser_remove_choice proto :ptr, :ptr
gtk_file_chooser_set_choice proto :ptr, :ptr, :ptr
gtk_file_chooser_get_choice proto :ptr, :ptr

endif

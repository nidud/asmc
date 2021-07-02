ifndef __GTK_FILE_CHOOSER_H__
__GTK_FILE_CHOOSER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilefilter.inc
include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_FILE_CHOOSER equ <gtk_file_chooser_get_type>
GTK_FILE_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER, GtkFileChooser))>
	endm
GTK_IS_FILE_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER))>
	endm

.enum GtkFileChooserAction {
  GTK_FILE_CHOOSER_ACTION_OPEN,
  GTK_FILE_CHOOSER_ACTION_SAVE,
  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
  GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER
}

.enum GtkFileChooserConfirmation {
  GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM,
  GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME,
  GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN
}

;GType
gtk_file_chooser_get_type proto __cdecl

GTK_FILE_CHOOSER_ERROR	equ <gtk_file_chooser_error_quark>

.enum GtkFileChooserError {
  GTK_FILE_CHOOSER_ERROR_NONEXISTENT,
  GTK_FILE_CHOOSER_ERROR_BAD_FILENAME,
  GTK_FILE_CHOOSER_ERROR_ALREADY_EXISTS,
  GTK_FILE_CHOOSER_ERROR_INCOMPLETE_HOSTNAME
}

;GQuark
gtk_file_chooser_error_quark proto __cdecl

;void
gtk_file_chooser_set_action proto __cdecl \
	       chooser: ptr GtkFileChooser,
		action: GtkFileChooserAction

;GtkFileChooserAction
gtk_file_chooser_get_action proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_set_local_only proto __cdecl \
	       chooser: ptr GtkFileChooser,
	    local_only: gboolean

;gboolean
gtk_file_chooser_get_local_only proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_set_select_multiple proto __cdecl \
	       chooser: ptr GtkFileChooser,
       select_multiple: gboolean

;gboolean
gtk_file_chooser_get_select_multiple proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_set_show_hidden proto __cdecl \
	       chooser: ptr GtkFileChooser,
	   show_hidden: gboolean

;gboolean
gtk_file_chooser_get_show_hidden proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_do_overwrite_confirmation proto __cdecl \
	       chooser: ptr GtkFileChooser,
do_overwrite_confirmation: gboolean

;gboolean
gtk_file_chooser_get_do_overwrite_confirmation proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_create_folders proto __cdecl \
	       chooser: ptr GtkFileChooser,
	create_folders: gboolean

;gboolean
gtk_file_chooser_get_create_folders proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_current_name proto __cdecl \
	       chooser: ptr GtkFileChooser,
		  name: ptr gchar

;gchar
gtk_file_chooser_get_current_name proto __cdecl \
	       chooser: ptr GtkFileChooser


;gchar
gtk_file_chooser_get_filename proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_filename proto __cdecl \
	       chooser: ptr GtkFileChooser,
	      filename: ptr char_t

;gboolean
gtk_file_chooser_select_filename proto __cdecl \
	       chooser: ptr GtkFileChooser,
	      filename: ptr char_t

;void
gtk_file_chooser_unselect_filename proto __cdecl \
	       chooser: ptr GtkFileChooser,
	      filename: ptr char_t

;void
gtk_file_chooser_select_all proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_unselect_all proto __cdecl \
	       chooser: ptr GtkFileChooser

;GSList
gtk_file_chooser_get_filenames proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_current_folder proto __cdecl \
	       chooser: ptr GtkFileChooser,
	      filename: ptr gchar

;gchar
gtk_file_chooser_get_current_folder proto __cdecl \
	       chooser: ptr GtkFileChooser



;gchar
gtk_file_chooser_get_uri proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr char_t

;gboolean
gtk_file_chooser_select_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr char_t

;void
gtk_file_chooser_unselect_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr char_t

;GSList
gtk_file_chooser_get_uris proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_current_folder_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr gchar

;gchar
gtk_file_chooser_get_current_folder_uri proto __cdecl \
	       chooser: ptr GtkFileChooser


;GFile
gtk_file_chooser_get_file proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_file proto __cdecl \
	       chooser: ptr GtkFileChooser,
		  file: ptr GFile,
		 error: ptr GError

;gboolean
gtk_file_chooser_select_file proto __cdecl \
	       chooser: ptr GtkFileChooser,
		  file: ptr GFile,
		 error: ptr GError

;void
gtk_file_chooser_unselect_file proto __cdecl \
	       chooser: ptr GtkFileChooser,
		  file: ptr GFile

;GSList
gtk_file_chooser_get_files proto __cdecl \
	       chooser: ptr GtkFileChooser

;gboolean
gtk_file_chooser_set_current_folder_file proto __cdecl \
	       chooser: ptr GtkFileChooser,
		  file: ptr GFile,
		 error: ptr GError

;GFile
gtk_file_chooser_get_current_folder_file proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_preview_widget proto __cdecl \
	       chooser: ptr GtkFileChooser,
	preview_widget: ptr GtkWidget

;GtkWidget
gtk_file_chooser_get_preview_widget proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_set_preview_widget_active proto __cdecl \
	       chooser: ptr GtkFileChooser,
		active: gboolean

;gboolean
gtk_file_chooser_get_preview_widget_active proto __cdecl \
	       chooser: ptr GtkFileChooser

;void
gtk_file_chooser_set_use_preview_label proto __cdecl \
	       chooser: ptr GtkFileChooser,
	     use_label: gboolean

;gboolean
gtk_file_chooser_get_use_preview_label proto __cdecl \
	       chooser: ptr GtkFileChooser


;char
gtk_file_chooser_get_preview_filename proto __cdecl \
	       chooser: ptr GtkFileChooser

;char
gtk_file_chooser_get_preview_uri proto __cdecl \
	       chooser: ptr GtkFileChooser

;GFile
gtk_file_chooser_get_preview_file proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_extra_widget proto __cdecl \
	       chooser: ptr GtkFileChooser,
	  extra_widget: ptr GtkWidget

;GtkWidget
gtk_file_chooser_get_extra_widget proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_add_filter proto __cdecl \
	       chooser: ptr GtkFileChooser,
		filter: ptr GtkFileFilter

;void
gtk_file_chooser_remove_filter proto __cdecl \
	       chooser: ptr GtkFileChooser,
		filter: ptr GtkFileFilter

;GSList
gtk_file_chooser_list_filters proto __cdecl \
	       chooser: ptr GtkFileChooser


;void
gtk_file_chooser_set_filter proto __cdecl \
	       chooser: ptr GtkFileChooser,
		filter: ptr GtkFileFilter

;GtkFileFilter
gtk_file_chooser_get_filter proto __cdecl \
	       chooser: ptr GtkFileChooser


;gboolean
gtk_file_chooser_add_shortcut_folder proto __cdecl \
	       chooser: ptr GtkFileChooser,
		folder: ptr char_t,
		 error: ptr GError

;gboolean
gtk_file_chooser_remove_shortcut_folder proto __cdecl \
	       chooser: ptr GtkFileChooser,
		folder: ptr char_t,
		 error: ptr GError

;GSList
gtk_file_chooser_list_shortcut_folders proto __cdecl \
	       chooser: ptr GtkFileChooser


;gboolean
gtk_file_chooser_add_shortcut_folder_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr char_t,
		 error: ptr GError

;gboolean
gtk_file_chooser_remove_shortcut_folder_uri proto __cdecl \
	       chooser: ptr GtkFileChooser,
		   uri: ptr char_t,
		 error: ptr GError

;GSList
gtk_file_chooser_list_shortcut_folder_uris proto __cdecl \
	       chooser: ptr GtkFileChooser


G_END_DECLS

endif

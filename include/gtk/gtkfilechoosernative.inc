ifndef __GTK_FILE_CHOOSER_NATIVE_H__
define __GTK_FILE_CHOOSER_NATIVE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilechooser.inc
include gtk/gtknativedialog.inc

define GTK_TYPE_FILE_CHOOSER_NATIVE <gtk_file_chooser_native_get_type>

gtk_file_chooser_native_new proto :ptr, :ptr, :GtkFileChooserAction, :ptr, :ptr
gtk_file_chooser_native_get_accept_label proto :ptr
gtk_file_chooser_native_set_accept_label proto :ptr, :ptr
gtk_file_chooser_native_get_cancel_label proto :ptr
gtk_file_chooser_native_set_cancel_label proto :ptr, :ptr

endif

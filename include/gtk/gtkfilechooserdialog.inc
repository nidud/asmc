ifndef __GTK_FILE_CHOOSER_DIALOG_H__
define __GTK_FILE_CHOOSER_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gtk/gtkfilechooser.inc

define GTK_TYPE_FILE_CHOOSER_DIALOG <gtk_file_chooser_dialog_get_type ()>
GTK_FILE_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER_DIALOG, GtkFileChooserDialog))>
  endm
GTK_IS_FILE_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER_DIALOG))>
  endm

gtk_file_chooser_dialog_get_type proto
gtk_file_chooser_dialog_new proto :ptr, :ptr, :GtkFileChooserAction, :ptr, :vararg

endif

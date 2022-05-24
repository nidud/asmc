ifndef __GTK_FILE_CHOOSER_WIDGET_H__
define __GTK_FILE_CHOOSER_WIDGET_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilechooser.inc
include gtk/gtkbox.inc

define GTK_TYPE_FILE_CHOOSER_WIDGET <gtk_file_chooser_widget_get_type ()>
GTK_FILE_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER_WIDGET, GtkFileChooserWidget))>
  endm
GTK_IS_FILE_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER_WIDGET))>
  endm

;GtkFileChooserWidget    typedef _GtkFileChooserWidget

gtk_file_chooser_widget_get_type proto
gtk_file_chooser_widget_new proto :GtkFileChooserAction

endif

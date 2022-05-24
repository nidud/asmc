ifndef __GTK_FILE_FILTER_H__
define __GTK_FILE_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

define GTK_TYPE_FILE_FILTER <gtk_file_filter_get_type ()>
GTK_FILE_FILTER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_FILTER, GtkFileFilter))>
  endm
GTK_IS_FILE_FILTER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_FILTER))>
  endm

;GtkFileFilter           typedef _GtkFileFilter

gtk_file_filter_get_type proto
gtk_file_filter_new proto
gtk_file_filter_set_name proto :ptr, :ptr
gtk_file_filter_get_name proto :ptr
gtk_file_filter_add_mime_type proto :ptr, :ptr
gtk_file_filter_add_pattern proto :ptr, :ptr
gtk_file_filter_add_suffix proto :ptr, :ptr
gtk_file_filter_add_pixbuf_formats proto :ptr
gtk_file_filter_get_attributes proto :ptr
gtk_file_filter_to_gvariant proto :ptr
gtk_file_filter_new_from_gvariant proto :ptr

endif

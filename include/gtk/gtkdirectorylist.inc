ifndef __GTK_DIRECTORY_LIST_H__
define __GTK_DIRECTORY_LIST_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gdk/gdk.inc

define GTK_TYPE_DIRECTORY_LIST <gtk_directory_list_get_type ()>

gtk_directory_list_new proto :ptr, :ptr

gtk_directory_list_set_file proto :ptr, :ptr
gtk_directory_list_get_file proto :ptr
gtk_directory_list_set_attributes proto :ptr, :ptr
gtk_directory_list_get_attributes proto :ptr
gtk_directory_list_set_io_priority proto :ptr, :sdword
gtk_directory_list_get_io_priority proto :ptr

gtk_directory_list_is_loading proto :ptr
gtk_directory_list_get_error proto :ptr

gtk_directory_list_set_monitored proto :ptr, :gboolean
gtk_directory_list_get_monitored proto :ptr

endif

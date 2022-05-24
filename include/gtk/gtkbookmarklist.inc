ifndef __GTK_BOOKMARK_LIST_H__
define __GTK_BOOKMARK_LIST_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gdk/gdk.inc

define GTK_TYPE_BOOKMARK_LIST <gtk_bookmark_list_get_type ()>

gtk_bookmark_list_new proto :ptr, :ptr
gtk_bookmark_list_get_filename proto :ptr
gtk_bookmark_list_set_attributes proto :ptr, :ptr
gtk_bookmark_list_get_attributes proto :ptr
gtk_bookmark_list_set_io_priority proto :ptr, :sdword
gtk_bookmark_list_get_io_priority proto :ptr
gtk_bookmark_list_is_loading proto :ptr

endif

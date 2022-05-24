ifndef __GTK_STRING_LIST_H__
define __GTK_STRING_LIST_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gdk/gdk.inc

define GTK_TYPE_STRING_OBJECT <gtk_string_object_get_type ()>

gtk_string_object_new proto :ptr
gtk_string_object_get_string proto :ptr

define GTK_TYPE_STRING_LIST <gtk_string_list_get_type ()>

gtk_string_list_new proto :ptr
gtk_string_list_append proto :ptr, :ptr
gtk_string_list_take proto :ptr, :ptr
gtk_string_list_remove proto :ptr, :guint
gtk_string_list_splice proto :ptr, :guint, :guint, :ptr
gtk_string_list_get_string proto :ptr, :guint

endif

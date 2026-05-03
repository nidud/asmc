ifndef __GTK_WINDOW_HANDLE_H__
define __GTK_WINDOW_HANDLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_WINDOW_HANDLE gtk_window_handle_get_type>

gtk_window_handle_new proto
gtk_window_handle_get_child proto :ptr
gtk_window_handle_set_child proto :ptr, :ptr

endif

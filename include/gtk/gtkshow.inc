ifndef __GTK_SHOW_H__
define __GTK_SHOW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

gtk_show_uri_full proto :ptr, :ptr, :guint32, :ptr, :GAsyncReadyCallback, :gpointer
gtk_show_uri_full_finish proto :ptr, :ptr, :ptr
gtk_show_uri proto :ptr, :ptr, :guint32

endif

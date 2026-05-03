ifndef __GTK_CUSTOM_FILTER_H__
define __GTK_CUSTOM_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilter.inc

CALLBACK(GtkCustomFilterFunc, :gpointer, :gpointer)

define GTK_TYPE_CUSTOM_FILTER <gtk_custom_filter_get_type ()>
gtk_custom_filter_new proto :GtkCustomFilterFunc, :gpointer, :GDestroyNotify
gtk_custom_filter_set_filter_func proto :ptr, :GtkCustomFilterFunc, :gpointer, :GDestroyNotify

endif

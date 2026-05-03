ifndef __GTK_CUSTOM_SORTER_H__
define __GTK_CUSTOM_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtksorter.inc

define GTK_TYPE_CUSTOM_SORTER <gtk_custom_sorter_get_type ()>

gtk_custom_sorter_new proto :GCompareDataFunc, :gpointer, :GDestroyNotify
gtk_custom_sorter_set_sort_func proto :ptr, :GCompareDataFunc, :gpointer, :GDestroyNotify

endif

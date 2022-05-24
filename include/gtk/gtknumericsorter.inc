ifndef __GTK_NUMERIC_SORTER_H__
define __GTK_NUMERIC_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtksorter.inc

define GTK_TYPE_NUMERIC_SORTER <gtk_numeric_sorter_get_type ()>

gtk_numeric_sorter_new proto :ptr
gtk_numeric_sorter_get_expression proto :ptr
gtk_numeric_sorter_set_expression proto :ptr, :ptr
gtk_numeric_sorter_get_sort_order proto :ptr
gtk_numeric_sorter_set_sort_order proto :ptr, :GtkSortType

endif

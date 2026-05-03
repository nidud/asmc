ifndef __GTK_TREE_LIST_ROW_SORTER_H__
define __GTK_TREE_LIST_ROW_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtksorter.inc

define GTK_TYPE_TREE_LIST_ROW_SORTER <gtk_tree_list_row_sorter_get_type ()>

gtk_tree_list_row_sorter_new proto :ptr
gtk_tree_list_row_sorter_get_sorter proto :ptr
gtk_tree_list_row_sorter_set_sorter proto :ptr, :ptr

endif

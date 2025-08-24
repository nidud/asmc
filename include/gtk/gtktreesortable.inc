ifndef __GTK_TREE_SORTABLE_H__
define __GTK_TREE_SORTABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkenums.inc
include gtk/gtktreemodel.inc

define GTK_TYPE_TREE_SORTABLE <gtk_tree_sortable_get_type ()>
GTK_TREE_SORTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_SORTABLE, GtkTreeSortable))>
  endm
GTK_IS_TREE_SORTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_SORTABLE))>
  endm
GTK_TREE_SORTABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_SORTABLE, GtkTreeSortableIface))>
  endm

define GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID (-1)
define GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID (-2)

CALLBACK(GtkTreeIterCompareFunc, :ptr, :ptr, :ptr, :gpointer)

GtkTreeSortableIface    struct
g_iface                 GTypeInterface <>
sort_column_changed     proc :ptr
get_sort_column_id      proc :ptr, :ptr, :ptr
set_sort_column_id      proc :ptr, :sdword, :GtkSortType
set_sort_func           proc :ptr, :sdword, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
set_default_sort_func   proc :ptr, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
has_default_sort_func   proc :ptr
GtkTreeSortableIface    ends

gtk_tree_sortable_get_type proto
gtk_tree_sortable_sort_column_changed proto :ptr
gtk_tree_sortable_get_sort_column_id proto :ptr, :ptr, :ptr
gtk_tree_sortable_set_sort_column_id proto :ptr, :sdword, :GtkSortType
gtk_tree_sortable_set_sort_func proto :ptr, :sdword, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
gtk_tree_sortable_set_default_sort_func proto :ptr, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
gtk_tree_sortable_has_default_sort_func proto :ptr

endif

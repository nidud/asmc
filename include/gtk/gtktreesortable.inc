ifndef __GTK_TREE_SORTABLE_H__
__GTK_TREE_SORTABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkenums.inc
include gtk/gtktreemodel.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_SORTABLE	equ <gtk_tree_sortable_get_type>
GTK_TREE_SORTABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_SORTABLE, GtkTreeSortable))>
	endm
GTK_TREE_SORTABLE_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_TYPE_TREE_SORTABLE, GtkTreeSortableIface))>
	endm
GTK_IS_TREE_SORTABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_SORTABLE))>
	endm
GTK_TREE_SORTABLE_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_SORTABLE, GtkTreeSortableIface))>
	endm

GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID equ (-1)

GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID equ (-2)

CALLBACKC(GtkTreeIterCompareFunc, :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GtkTreeIter, :gpointer)

GtkTreeSortableIface	STRUC
g_iface			GTypeInterface <>
sort_column_changed	proc :ptr GtkTreeSortable
get_sort_column_id	proc :ptr GtkTreeSortable, :ptr gint, :ptr GtkSortType
set_sort_column_id	proc :ptr GtkTreeSortable, :gint, :GtkSortType
set_sort_func		proc :ptr GtkTreeSortable, :gint, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
set_default_sort_func	proc :ptr GtkTreeSortable, :GtkTreeIterCompareFunc, :gpointer, :GDestroyNotify
has_default_sort_func	proc :ptr GtkTreeSortable
GtkTreeSortableIface	ENDS


;GType
gtk_tree_sortable_get_type proto __cdecl

;void
gtk_tree_sortable_sort_column_changed proto __cdecl \
	      sortable: ptr GtkTreeSortable

;gboolean
gtk_tree_sortable_get_sort_column_id proto __cdecl \
	      sortable: ptr GtkTreeSortable,
	sort_column_id: ptr gint,
		 order: ptr GtkSortType

;void
gtk_tree_sortable_set_sort_column_id proto __cdecl \
	      sortable: ptr GtkTreeSortable,
	sort_column_id: gint,
		 order: GtkSortType

;void
gtk_tree_sortable_set_sort_func proto __cdecl \
	      sortable: ptr GtkTreeSortable,
	sort_column_id: gint,
	     sort_func: GtkTreeIterCompareFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_tree_sortable_set_default_sort_func proto __cdecl \
	      sortable: ptr GtkTreeSortable,
	     sort_func: GtkTreeIterCompareFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;gboolean
gtk_tree_sortable_has_default_sort_func proto __cdecl \
	      sortable: ptr GtkTreeSortable


G_END_DECLS

endif

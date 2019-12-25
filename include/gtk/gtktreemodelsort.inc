ifndef __GTK_TREE_MODEL_SORT_H__
__GTK_TREE_MODEL_SORT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_MODEL_SORT equ <gtk_tree_model_sort_get_type>
GTK_TREE_MODEL_SORT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_MODEL_SORT, GtkTreeModelSort))>
	endm
GTK_TREE_MODEL_SORT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_MODEL_SORT, GtkTreeModelSortClass))>
	endm
GTK_IS_TREE_MODEL_SORT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_MODEL_SORT))>
	endm
GTK_IS_TREE_MODEL_SORT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_MODEL_SORT))>
	endm
GTK_TREE_MODEL_SORT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_MODEL_SORT, GtkTreeModelSortClass))>
	endm

GtkTreeModelSort	STRUC
parent			GObject <>
priv			ptr_t ?
GtkTreeModelSort	ENDS

GtkTreeModelSortClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTreeModelSortClass	ENDS


;GType
gtk_tree_model_sort_get_type proto __cdecl
;GtkTreeModel
gtk_tree_model_sort_new_with_model proto __cdecl \
	   child_model: ptr GtkTreeModel


;GtkTreeModel
gtk_tree_model_sort_get_model proto __cdecl \
	    tree_model: ptr GtkTreeModelSort

;GtkTreePath
gtk_tree_model_sort_convert_child_path_to_path proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort,
	    child_path: ptr GtkTreePath

;gboolean
gtk_tree_model_sort_convert_child_iter_to_iter proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort,
	     sort_iter: ptr GtkTreeIter,
	    child_iter: ptr GtkTreeIter

;GtkTreePath
gtk_tree_model_sort_convert_path_to_child_path proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort,
	   sorted_path: ptr GtkTreePath

;void
gtk_tree_model_sort_convert_iter_to_child_iter proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort,
	    child_iter: ptr GtkTreeIter,
	   sorted_iter: ptr GtkTreeIter

;void
gtk_tree_model_sort_reset_default_sort_func proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort

;void
gtk_tree_model_sort_clear_cache proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort

;gboolean
gtk_tree_model_sort_iter_is_valid proto __cdecl \
       tree_model_sort: ptr GtkTreeModelSort,
		  iter: ptr GtkTreeIter

G_END_DECLS

endif

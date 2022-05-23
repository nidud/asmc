ifndef __GTK_TREE_MODEL_SORT_H__
define __GTK_TREE_MODEL_SORT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc

define GTK_TYPE_TREE_MODEL_SORT <gtk_tree_model_sort_get_type>
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

;GtkTreeModelSortPrivate typedef _GtkTreeModelSortPrivate

_GtkTreeModelSort	struct
parent			GObject <>
priv			ptr GtkTreeModelSortPrivate ?
_GtkTreeModelSort	ends
GtkTreeModelSort	typedef _GtkTreeModelSort

_GtkTreeModelSortClass	struct
parent_class		GObjectClass <>
padding			gpointer 8 dup(?)
_GtkTreeModelSortClass	ends
GtkTreeModelSortClass	typedef _GtkTreeModelSortClass


gtk_tree_model_sort_get_type proto
gtk_tree_model_sort_new_with_model proto :ptr
gtk_tree_model_sort_get_model proto :ptr
gtk_tree_model_sort_convert_child_path_to_path proto :ptr, :ptr
gtk_tree_model_sort_convert_child_iter_to_iter proto :ptr, :ptr, :ptr
gtk_tree_model_sort_convert_path_to_child_path proto :ptr, :ptr
gtk_tree_model_sort_convert_iter_to_child_iter proto :ptr, :ptr, :ptr
gtk_tree_model_sort_reset_default_sort_func proto :ptr
gtk_tree_model_sort_clear_cache proto :ptr
gtk_tree_model_sort_iter_is_valid proto :ptr, :ptr

endif

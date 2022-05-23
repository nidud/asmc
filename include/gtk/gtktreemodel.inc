ifndef __GTK_TREE_MODEL_H__
define __GTK_TREE_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

define GTK_TYPE_TREE_MODEL <gtk_tree_model_get_type>
GTK_TREE_MODEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_MODEL, GtkTreeModel))>
  endm
GTK_IS_TREE_MODEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_MODEL))>
  endm
GTK_TREE_MODEL_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_MODEL, GtkTreeModelIface))>
  endm

define GTK_TYPE_TREE_ITER             <gtk_tree_iter_get_type>
define GTK_TYPE_TREE_PATH             <gtk_tree_path_get_type>
define GTK_TYPE_TREE_ROW_REFERENCE    <gtk_tree_row_reference_get_type>

;GtkTreePath             typedef _GtkTreePath
;GtkTreeRowReference     typedef _GtkTreeRowReference
;GtkTreeModel            typedef _GtkTreeModel

CALLBACK(GtkTreeModelForeachFunc, :ptr, :ptr, :ptr, :gpointer)

.enum GtkTreeModelFlags {
  GTK_TREE_MODEL_ITERS_PERSIST = 1 shl 0,
  GTK_TREE_MODEL_LIST_ONLY = 1 shl 1
}

_GtkTreeIter            struct
stamp                   sdword ?
user_data               gpointer ?
user_data2              gpointer ?
user_data3              gpointer ?
_GtkTreeIter            ends
GtkTreeIter             typedef _GtkTreeIter

_GtkTreeModelIface      struct
g_iface                 GTypeInterface <>
row_changed             proc :ptr, :ptr, :ptr
row_inserted            proc :ptr, :ptr, :ptr
row_has_child_toggled   proc :ptr, :ptr, :ptr
row_deleted             proc :ptr, :ptr
rows_reordered          proc :ptr, :ptr, :ptr, :ptr
get_flags               proc :ptr
get_n_columns           proc :ptr
get_column_type         proc :ptr, :sdword
get_iter                proc :ptr, :ptr, :ptr
get_path                proc :ptr, :ptr
get_value               proc :ptr, :ptr, :sdword, :ptr
iter_next               proc :ptr, :ptr
iter_previous           proc :ptr, :ptr
iter_children           proc :ptr, :ptr, :ptr
iter_has_child          proc :ptr, :ptr
iter_n_children         proc :ptr, :ptr
iter_nth_child          proc :ptr, :ptr, :ptr, :sdword
iter_parent             proc :ptr, :ptr, :ptr
ref_node                proc :ptr, :ptr
unref_node              proc :ptr, :ptr
_GtkTreeModelIface      ends
GtkTreeModelIface       typedef _GtkTreeModelIface

gtk_tree_path_new proto
gtk_tree_path_new_from_string proto :ptr
gtk_tree_path_new_from_indices proto :sdword, :vararg
gtk_tree_path_new_from_indicesv proto :ptr, :gsize
gtk_tree_path_to_string proto :ptr
gtk_tree_path_new_first proto
gtk_tree_path_append_index proto :ptr, :sdword
gtk_tree_path_prepend_index proto :ptr, :sdword
gtk_tree_path_get_depth proto :ptr
gtk_tree_path_get_indices proto :ptr
gtk_tree_path_get_indices_with_depth proto :ptr, :ptr
gtk_tree_path_free proto :ptr
gtk_tree_path_copy proto :ptr
gtk_tree_path_get_type proto
gtk_tree_path_compare proto :ptr, :ptr
gtk_tree_path_next proto :ptr
gtk_tree_path_prev proto :ptr
gtk_tree_path_up proto :ptr
gtk_tree_path_down proto :ptr
gtk_tree_path_is_ancestor proto :ptr, :ptr
gtk_tree_path_is_descendant proto :ptr, :ptr
gtk_tree_row_reference_get_type proto
gtk_tree_row_reference_new proto :ptr, :ptr
gtk_tree_row_reference_new_proxy proto :ptr, :ptr, :ptr
gtk_tree_row_reference_get_path proto :ptr
gtk_tree_row_reference_get_model proto :ptr
gtk_tree_row_reference_valid proto :ptr
gtk_tree_row_reference_copy proto :ptr
gtk_tree_row_reference_free proto :ptr
gtk_tree_row_reference_inserted proto :ptr, :ptr
gtk_tree_row_reference_deleted proto :ptr, :ptr
gtk_tree_row_reference_reordered proto :ptr, :ptr, :ptr, :ptr
gtk_tree_iter_copy proto :ptr
gtk_tree_iter_free proto :ptr
gtk_tree_iter_get_type proto
gtk_tree_model_get_type proto
gtk_tree_model_get_flags proto :ptr
gtk_tree_model_get_n_columns proto :ptr
gtk_tree_model_get_column_type proto :ptr, :sdword

gtk_tree_model_get_iter proto :ptr, :ptr, :ptr
gtk_tree_model_get_iter_from_string proto :ptr, :ptr, :ptr
gtk_tree_model_get_string_from_iter proto :ptr, :ptr
gtk_tree_model_get_iter_first proto :ptr, :ptr
gtk_tree_model_get_path proto :ptr, :ptr
gtk_tree_model_get_value proto :ptr, :ptr, :sdword, :ptr
gtk_tree_model_iter_previous proto :ptr, :ptr
gtk_tree_model_iter_next proto :ptr, :ptr
gtk_tree_model_iter_children proto :ptr, :ptr, :ptr
gtk_tree_model_iter_has_child proto :ptr, :ptr
gtk_tree_model_iter_n_children proto :ptr, :ptr
gtk_tree_model_iter_nth_child proto :ptr, :ptr, :ptr, :sdword
gtk_tree_model_iter_parent proto :ptr, :ptr, :ptr
gtk_tree_model_ref_node proto :ptr, :ptr
gtk_tree_model_unref_node proto :ptr, :ptr
gtk_tree_model_get proto :ptr, :ptr, :vararg
gtk_tree_model_get_valist proto :ptr, :ptr, :va_list

gtk_tree_model_foreach proto :ptr, :GtkTreeModelForeachFunc, :gpointer

gtk_tree_model_row_changed proto :ptr, :ptr, :ptr
gtk_tree_model_row_inserted proto :ptr, :ptr, :ptr
gtk_tree_model_row_has_child_toggled proto :ptr, :ptr, :ptr
gtk_tree_model_row_deleted proto :ptr, :ptr
gtk_tree_model_rows_reordered proto :ptr, :ptr, :ptr, :ptr
gtk_tree_model_rows_reordered_with_length proto :ptr, :ptr, :ptr, :ptr, :sdword

endif

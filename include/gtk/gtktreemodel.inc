ifndef __GTK_TREE_MODEL_H__
__GTK_TREE_MODEL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_MODEL equ <gtk_tree_model_get_type>
GTK_TREE_MODEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_MODEL, GtkTreeModel))>
	endm
GTK_IS_TREE_MODEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_MODEL))>
	endm
GTK_TREE_MODEL_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_MODEL, GtkTreeModelIface))>
	endm

GTK_TYPE_TREE_ITER  equ <gtk_tree_iter_get_type>
GTK_TYPE_TREE_PATH  equ <gtk_tree_path_get_type>
GTK_TYPE_TREE_ROW_REFERENCE equ <gtk_tree_row_reference_get_type>


CALLBACKC(GtkTreeModelForeachFunc, :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter, :gpointer)

.enum GtkTreeModelFlags {
  GTK_TREE_MODEL_ITERS_PERSIST = 1 shl 0,
  GTK_TREE_MODEL_LIST_ONLY     = 1 shl 1
}

GtkTreeIter		STRUC
stamp			gint ?
user_data		gpointer ?
user_data2		gpointer ?
user_data3		gpointer ?
GtkTreeIter		ENDS

GtkTreeModelIface	STRUC
g_iface			GTypeInterface <>
row_changed		proc :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter
row_inserted		proc :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter
row_has_child_toggled	proc :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter
row_deleted		proc :ptr GtkTreeModel, :ptr GtkTreePath
rows_reordered		proc :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter, :ptr gint
get_flags		proc :ptr GtkTreeModel
get_n_columns		proc :ptr GtkTreeModel
get_column_type		proc :ptr GtkTreeModel, :gint
get_iter		proc :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GtkTreePath
get_path		proc :ptr GtkTreeModel, :ptr GtkTreeIter
get_value		proc :ptr GtkTreeModel, :ptr GtkTreeIter, :gint, :ptr GValue
iter_next		proc :ptr GtkTreeModel, :ptr GtkTreeIter
iter_previous		proc :ptr GtkTreeModel, :ptr GtkTreeIter
iter_children		proc :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GtkTreeIter
iter_has_child		proc :ptr GtkTreeModel, :ptr GtkTreeIter
iter_n_children		proc :ptr GtkTreeModel, :ptr GtkTreeIter
iter_nth_child		proc :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GtkTreeIter, :gint
iter_parent		proc :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GtkTreeIter
ref_node		proc :ptr GtkTreeModel, :ptr GtkTreeIter
unref_node		proc :ptr GtkTreeModel, :ptr GtkTreeIter
GtkTreeModelIface	ENDS


;GtkTreePath
gtk_tree_path_new proto __cdecl
;GtkTreePath
gtk_tree_path_new_from_string proto __cdecl \
		  path: ptr gchar

;GtkTreePath
gtk_tree_path_new_from_indices proto _CDecl \
	   first_index: gint,
		      : vararg

;GtkTreePath
gtk_tree_path_new_from_indicesv proto __cdecl \
	       indices: ptr gint,
		length: gsize

;gchar
gtk_tree_path_to_string proto __cdecl \
		  path: ptr GtkTreePath

;GtkTreePath
gtk_tree_path_new_first proto __cdecl
;void
gtk_tree_path_append_index proto __cdecl \
		  path: ptr GtkTreePath,
		index_: gint

;void
gtk_tree_path_prepend_index proto __cdecl \
		  path: ptr GtkTreePath,
		index_: gint

;gint
gtk_tree_path_get_depth proto __cdecl \
		  path: ptr GtkTreePath

;gint
gtk_tree_path_get_indices proto __cdecl \
		  path: ptr GtkTreePath


;gint
gtk_tree_path_get_indices_with_depth proto __cdecl \
		  path: ptr GtkTreePath,
		 depth: ptr gint


;void
gtk_tree_path_free proto __cdecl \
		  path: ptr GtkTreePath

;GtkTreePath
gtk_tree_path_copy proto __cdecl \
		  path: ptr GtkTreePath

;GType
gtk_tree_path_get_type proto __cdecl
;gint
gtk_tree_path_compare proto __cdecl \
		     a: ptr GtkTreePath,
		     b: ptr GtkTreePath

;void
gtk_tree_path_next proto __cdecl \
		  path: ptr GtkTreePath

;gboolean
gtk_tree_path_prev proto __cdecl \
		  path: ptr GtkTreePath

;gboolean
gtk_tree_path_up proto __cdecl \
		  path: ptr GtkTreePath

;void
gtk_tree_path_down proto __cdecl \
		  path: ptr GtkTreePath


;gboolean
gtk_tree_path_is_ancestor proto __cdecl \
		  path: ptr GtkTreePath,
	    descendant: ptr GtkTreePath

;gboolean
gtk_tree_path_is_descendant proto __cdecl \
		  path: ptr GtkTreePath,
	      ancestor: ptr GtkTreePath



;GType
gtk_tree_row_reference_get_type proto __cdecl
;GtkTreeRowReference
gtk_tree_row_reference_new proto __cdecl \
		 model: ptr GtkTreeModel,
		  path: ptr GtkTreePath

;GtkTreeRowReference
gtk_tree_row_reference_new_proxy proto __cdecl \
		 proxy: ptr GObject,
		 model: ptr GtkTreeModel,
		  path: ptr GtkTreePath

;GtkTreePath
gtk_tree_row_reference_get_path proto __cdecl \
	     reference: ptr GtkTreeRowReference

;GtkTreeModel
gtk_tree_row_reference_get_model proto __cdecl \
	     reference: ptr GtkTreeRowReference

;gboolean
gtk_tree_row_reference_valid proto __cdecl \
	     reference: ptr GtkTreeRowReference

;GtkTreeRowReference
gtk_tree_row_reference_copy proto __cdecl \
	     reference: ptr GtkTreeRowReference

;void
gtk_tree_row_reference_free proto __cdecl \
	     reference: ptr GtkTreeRowReference

;void
gtk_tree_row_reference_inserted proto __cdecl \
		 proxy: ptr GObject,
		  path: ptr GtkTreePath

;void
gtk_tree_row_reference_deleted proto __cdecl \
		 proxy: ptr GObject,
		  path: ptr GtkTreePath

;void
gtk_tree_row_reference_reordered proto __cdecl \
		 proxy: ptr GObject,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter,
	     new_order: ptr gint


;GtkTreeIter
gtk_tree_iter_copy proto __cdecl \
		  iter: ptr GtkTreeIter

;void
gtk_tree_iter_free proto __cdecl \
		  iter: ptr GtkTreeIter

;GType
gtk_tree_iter_get_type proto __cdecl

;GType
gtk_tree_model_get_type proto __cdecl
;GtkTreeModelFlags
gtk_tree_model_get_flags proto __cdecl \
	    tree_model: ptr GtkTreeModel

;gint
gtk_tree_model_get_n_columns proto __cdecl \
	    tree_model: ptr GtkTreeModel

;GType
gtk_tree_model_get_column_type proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		index_: gint



;gboolean
gtk_tree_model_get_iter proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		  path: ptr GtkTreePath

;gboolean
gtk_tree_model_get_iter_from_string proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
	   path_string: ptr gchar

;gchar
gtk_tree_model_get_string_from_iter proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;gboolean
gtk_tree_model_get_iter_first proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;GtkTreePath
gtk_tree_model_get_path proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_get_value proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		column: gint,
		 value: ptr GValue

;gboolean
gtk_tree_model_iter_previous proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;gboolean
gtk_tree_model_iter_next proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;gboolean
gtk_tree_model_iter_children proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter

;gboolean
gtk_tree_model_iter_has_child proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;gint
gtk_tree_model_iter_n_children proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;gboolean
gtk_tree_model_iter_nth_child proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
		     n: gint

;gboolean
gtk_tree_model_iter_parent proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		 child: ptr GtkTreeIter

;void
gtk_tree_model_ref_node proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_unref_node proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_get proto _CDecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
		      : vararg

;void
gtk_tree_model_get_valist proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
	      var_args: va_list



;void
gtk_tree_model_foreach proto __cdecl \
		 model: ptr GtkTreeModel,
		  func: GtkTreeModelForeachFunc,
	     user_data: gpointer


;void
gtk_tree_model_row_changed proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_row_inserted proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_row_has_child_toggled proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter

;void
gtk_tree_model_row_deleted proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath

;void
gtk_tree_model_rows_reordered proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter,
	     new_order: ptr gint

;void
gtk_tree_model_rows_reordered_with_length proto __cdecl \
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter,
	     new_order: ptr gint,
		length: gint

G_END_DECLS

endif

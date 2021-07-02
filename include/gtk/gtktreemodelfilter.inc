ifndef __GTK_TREE_MODEL_FILTER_H__
__GTK_TREE_MODEL_FILTER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_MODEL_FILTER equ <gtk_tree_model_filter_get_type>
GTK_TREE_MODEL_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_MODEL_FILTER, GtkTreeModelFilter))>
	endm
GTK_TREE_MODEL_FILTER_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_CAST ((vtable), GTK_TYPE_TREE_MODEL_FILTER, GtkTreeModelFilterClass))>
	endm
GTK_IS_TREE_MODEL_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_MODEL_FILTER))>
	endm
GTK_IS_TREE_MODEL_FILTER_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((vtable), GTK_TYPE_TREE_MODEL_FILTER))>
	endm
GTK_TREE_MODEL_FILTER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_MODEL_FILTER, GtkTreeModelFilterClass))>
	endm

CALLBACKC(GtkTreeModelFilterVisibleFunc, :ptr GtkTreeModel, :ptr GtkTreeIter, :gpointer)
CALLBACKC(GtkTreeModelFilterModifyFunc, :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GValue, :gint, :gpointer)

GtkTreeModelFilter	STRUC
parent			GObject <>
priv			ptr_t ?
GtkTreeModelFilter	ENDS

GtkTreeModelFilterClass STRUC
parent_class		GObjectClass <>
visible			proc :ptr GtkTreeModelFilter, :ptr GtkTreeModel, :ptr GtkTreeIter
modify			proc :ptr GtkTreeModelFilter, :ptr GtkTreeModel, :ptr GtkTreeIter, :ptr GValue, :gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTreeModelFilterClass ENDS

;GType
gtk_tree_model_filter_get_type proto __cdecl
;GtkTreeModel
gtk_tree_model_filter_new proto __cdecl \
	   child_model: ptr GtkTreeModel,
		  root: ptr GtkTreePath

;void
gtk_tree_model_filter_set_visible_func proto __cdecl \
		filter: ptr GtkTreeModelFilter,
		  func: GtkTreeModelFilterVisibleFunc,
		  data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_tree_model_filter_set_modify_func proto __cdecl \
		filter: ptr GtkTreeModelFilter,
	     n_columns: gint,
		 types: ptr GType,
		  func: GtkTreeModelFilterModifyFunc,
		  data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_tree_model_filter_set_visible_column proto __cdecl \
		filter: ptr GtkTreeModelFilter,
		column: gint


;GtkTreeModel
gtk_tree_model_filter_get_model proto __cdecl \
		filter: ptr GtkTreeModelFilter


;gboolean
gtk_tree_model_filter_convert_child_iter_to_iter proto __cdecl \
		filter: ptr GtkTreeModelFilter,
	   filter_iter: ptr GtkTreeIter,
	    child_iter: ptr GtkTreeIter

;void
gtk_tree_model_filter_convert_iter_to_child_iter proto __cdecl \
		filter: ptr GtkTreeModelFilter,
	    child_iter: ptr GtkTreeIter,
	   filter_iter: ptr GtkTreeIter

;GtkTreePath
gtk_tree_model_filter_convert_child_path_to_path proto __cdecl \
		filter: ptr GtkTreeModelFilter,
	    child_path: ptr GtkTreePath

;GtkTreePath
gtk_tree_model_filter_convert_path_to_child_path proto __cdecl \
		filter: ptr GtkTreeModelFilter,
	   filter_path: ptr GtkTreePath


;void
gtk_tree_model_filter_refilter proto __cdecl \
		filter: ptr GtkTreeModelFilter

;void
gtk_tree_model_filter_clear_cache proto __cdecl \
		filter: ptr GtkTreeModelFilter

G_END_DECLS

endif

ifndef __GTK_TREE_MODEL_FILTER_H__
define __GTK_TREE_MODEL_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc

define GTK_TYPE_TREE_MODEL_FILTER <gtk_tree_model_filter_get_type ()>
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


CALLBACK(GtkTreeModelFilterVisibleFunc, :ptr, :ptr, :gpointer)
CALLBACK(GtkTreeModelFilterModifyFunc, :ptr, :ptr, :ptr, :sdword, :gpointer)

;GtkTreeModelFilterPrivate typedef _GtkTreeModelFilterPrivate

_GtkTreeModelFilter     struct
parent                  GObject <>
priv                    ptr GtkTreeModelFilterPrivate ?
_GtkTreeModelFilter     ends
GtkTreeModelFilter      typedef _GtkTreeModelFilter

_GtkTreeModelFilterClass struct
parent_class            GObjectClass <>
visible                 proc :ptr, :ptr, :ptr
modify                  proc :ptr, :ptr, :ptr, :ptr, :sdword
padding                 gpointer 8 dup(?)
_GtkTreeModelFilterClass ends
GtkTreeModelFilterClass typedef _GtkTreeModelFilterClass


gtk_tree_model_filter_get_type proto
gtk_tree_model_filter_new proto :ptr, :ptr
gtk_tree_model_filter_set_visible_func proto :ptr, :GtkTreeModelFilterVisibleFunc, :gpointer, :GDestroyNotify
gtk_tree_model_filter_set_modify_func proto :ptr, :sdword, :ptr, :GtkTreeModelFilterModifyFunc, :gpointer, :GDestroyNotify
gtk_tree_model_filter_set_visible_column proto :ptr, :sdword
gtk_tree_model_filter_get_model proto :ptr
gtk_tree_model_filter_convert_child_iter_to_iter proto :ptr, :ptr, :ptr
gtk_tree_model_filter_convert_iter_to_child_iter proto :ptr, :ptr, :ptr
gtk_tree_model_filter_convert_child_path_to_path proto :ptr, :ptr
gtk_tree_model_filter_convert_path_to_child_path proto :ptr, :ptr
gtk_tree_model_filter_refilter proto :ptr
gtk_tree_model_filter_clear_cache proto :ptr

endif

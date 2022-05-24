ifndef __GTK_TREE_LIST_MODEL_H__
define __GTK_TREE_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_TREE_LIST_MODEL <gtk_tree_list_model_get_type ()>
define GTK_TYPE_TREE_LIST_ROW <gtk_tree_list_row_get_type ()>

CALLBACK(GtkTreeListModelCreateModelFunc, :gpointer, :gpointer)

gtk_tree_list_model_new proto :ptr, :gboolean, :gboolean, :GtkTreeListModelCreateModelFunc, :gpointer, :GDestroyNotify
gtk_tree_list_model_get_model proto :ptr
gtk_tree_list_model_get_passthrough proto :ptr
gtk_tree_list_model_set_autoexpand proto :ptr, :gboolean
gtk_tree_list_model_get_autoexpand proto :ptr
gtk_tree_list_model_get_child_row proto :ptr, :guint
gtk_tree_list_model_get_row proto :ptr, :guint
gtk_tree_list_row_get_item proto :ptr
gtk_tree_list_row_set_expanded proto :ptr, :gboolean
gtk_tree_list_row_get_expanded proto :ptr
gtk_tree_list_row_is_expandable proto :ptr
gtk_tree_list_row_get_position proto :ptr
gtk_tree_list_row_get_depth proto :ptr
gtk_tree_list_row_get_children proto :ptr
gtk_tree_list_row_get_parent proto :ptr
gtk_tree_list_row_get_child_row proto :ptr, :guint

endif

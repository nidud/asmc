ifndef __GTK_TREE_SELECTION_H__
define __GTK_TREE_SELECTION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreeview.inc

define GTK_TYPE_TREE_SELECTION <gtk_tree_selection_get_type>
GTK_TREE_SELECTION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_SELECTION, GtkTreeSelection))>
  endm
GTK_IS_TREE_SELECTION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_SELECTION))>
  endm


CALLBACK(GtkTreeSelectionFunc, :ptr, :ptr, :ptr, :gboolean, :gpointer)
CALLBACK(GtkTreeSelectionForeachFunc, :ptr, :ptr, :ptr, :gpointer)

gtk_tree_selection_get_type proto
gtk_tree_selection_set_mode proto :ptr, :GtkSelectionMode
gtk_tree_selection_get_mode proto :ptr
gtk_tree_selection_set_select_function proto :ptr, :GtkTreeSelectionFunc, :gpointer, :GDestroyNotify
gtk_tree_selection_get_user_data proto :ptr
gtk_tree_selection_get_tree_view proto :ptr
gtk_tree_selection_get_select_function proto :ptr
gtk_tree_selection_get_selected proto :ptr, :ptr, :ptr
gtk_tree_selection_get_selected_rows proto :ptr, :ptr
gtk_tree_selection_count_selected_rows proto :ptr
gtk_tree_selection_selected_foreach proto :ptr, :GtkTreeSelectionForeachFunc, :gpointer
gtk_tree_selection_select_path proto :ptr, :ptr
gtk_tree_selection_unselect_path proto :ptr, :ptr
gtk_tree_selection_select_iter proto :ptr, :ptr
gtk_tree_selection_unselect_iter proto :ptr, :ptr
gtk_tree_selection_path_is_selected proto :ptr, :ptr
gtk_tree_selection_iter_is_selected proto :ptr, :ptr
gtk_tree_selection_select_all proto :ptr
gtk_tree_selection_unselect_all proto :ptr
gtk_tree_selection_select_range proto :ptr, :ptr, :ptr
gtk_tree_selection_unselect_range proto :ptr, :ptr, :ptr

endif

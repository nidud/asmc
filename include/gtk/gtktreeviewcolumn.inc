ifndef __GTK_TREE_VIEW_COLUMN_H__
define __GTK_TREE_VIEW_COLUMN_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc
include gtk/gtkcellarea.inc

define GTK_TYPE_TREE_VIEW_COLUMN <gtk_tree_view_column_get_type ()>
GTK_TREE_VIEW_COLUMN macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_VIEW_COLUMN, GtkTreeViewColumn))>
  endm
GTK_IS_TREE_VIEW_COLUMN macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_VIEW_COLUMN))>
  endm

;GtkTreeViewColumn	 typedef _GtkTreeViewColumn

.enum GtkTreeViewColumnSizing {
  GTK_TREE_VIEW_COLUMN_GROW_ONLY,
  GTK_TREE_VIEW_COLUMN_AUTOSIZE,
  GTK_TREE_VIEW_COLUMN_FIXED
}


CALLBACK(GtkTreeCellDataFunc, :ptr, :ptr, :ptr, :ptr, :gpointer)

gtk_tree_view_column_get_type proto
gtk_tree_view_column_new proto
gtk_tree_view_column_new_with_area proto :ptr
gtk_tree_view_column_new_with_attributes proto :ptr, :ptr, :vararg
gtk_tree_view_column_pack_start proto :ptr, :ptr, :gboolean
gtk_tree_view_column_pack_end proto :ptr, :ptr, :gboolean
gtk_tree_view_column_clear proto :ptr
gtk_tree_view_column_add_attribute proto :ptr, :ptr, :ptr, :sdword
gtk_tree_view_column_set_attributes proto :ptr, :ptr, :vararg
gtk_tree_view_column_set_cell_data_func proto :ptr, :ptr, :GtkTreeCellDataFunc, :gpointer, :GDestroyNotify
gtk_tree_view_column_clear_attributes proto :ptr, :ptr
gtk_tree_view_column_set_spacing proto :ptr, :sdword
gtk_tree_view_column_get_spacing proto :ptr
gtk_tree_view_column_set_visible proto :ptr, :gboolean
gtk_tree_view_column_get_visible proto :ptr
gtk_tree_view_column_set_resizable proto :ptr, :gboolean
gtk_tree_view_column_get_resizable proto :ptr
gtk_tree_view_column_set_sizing proto :ptr, :GtkTreeViewColumnSizing
gtk_tree_view_column_get_sizing proto :ptr
gtk_tree_view_column_get_x_offset proto :ptr
gtk_tree_view_column_get_width proto :ptr
gtk_tree_view_column_get_fixed_width proto :ptr
gtk_tree_view_column_set_fixed_width proto :ptr, :sdword
gtk_tree_view_column_set_min_width proto :ptr, :sdword
gtk_tree_view_column_get_min_width proto :ptr
gtk_tree_view_column_set_max_width proto :ptr, :sdword
gtk_tree_view_column_get_max_width proto :ptr
gtk_tree_view_column_clicked proto :ptr

gtk_tree_view_column_set_title proto :ptr, :ptr
gtk_tree_view_column_get_title proto :ptr
gtk_tree_view_column_set_expand proto :ptr, :gboolean
gtk_tree_view_column_get_expand proto :ptr
gtk_tree_view_column_set_clickable proto :ptr, :gboolean
gtk_tree_view_column_get_clickable proto :ptr
gtk_tree_view_column_set_widget proto :ptr, :ptr
gtk_tree_view_column_get_widget proto :ptr
gtk_tree_view_column_set_alignment proto :ptr, :real4
gtk_tree_view_column_get_alignment proto :ptr
gtk_tree_view_column_set_reorderable proto :ptr, :gboolean
gtk_tree_view_column_get_reorderable proto :ptr

gtk_tree_view_column_set_sort_column_id proto :ptr, :sdword
gtk_tree_view_column_get_sort_column_id proto :ptr
gtk_tree_view_column_set_sort_indicator proto :ptr, :gboolean
gtk_tree_view_column_get_sort_indicator proto :ptr
gtk_tree_view_column_set_sort_order proto :ptr, :GtkSortType
gtk_tree_view_column_get_sort_order proto :ptr

gtk_tree_view_column_cell_set_cell_data proto :ptr, :ptr, :ptr, :gboolean, :gboolean
gtk_tree_view_column_cell_get_size proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_tree_view_column_cell_is_visible proto :ptr
gtk_tree_view_column_focus_cell proto :ptr, :ptr
gtk_tree_view_column_cell_get_position proto :ptr, :ptr, :ptr, :ptr
gtk_tree_view_column_queue_resize proto :ptr
gtk_tree_view_column_get_tree_view proto :ptr
gtk_tree_view_column_get_button proto :ptr

endif

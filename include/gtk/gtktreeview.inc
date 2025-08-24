ifndef __GTK_TREE_VIEW_H__
define __GTK_TREE_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtktreemodel.inc
include gtk/gtktreeviewcolumn.inc
include gtk/gtkentry.inc

.enum GtkTreeViewDropPosition {
  GTK_TREE_VIEW_DROP_BEFORE,
  GTK_TREE_VIEW_DROP_AFTER,
  GTK_TREE_VIEW_DROP_INTO_OR_BEFORE,
  GTK_TREE_VIEW_DROP_INTO_OR_AFTER
}

define GTK_TYPE_TREE_VIEW <gtk_tree_view_get_type ()>
GTK_TREE_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_VIEW, GtkTreeView))>
  endm
GTK_IS_TREE_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_VIEW))>
  endm
GTK_TREE_VIEW_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_VIEW, GtkTreeViewClass))>
  endm
GTK_IS_TREE_VIEW_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_VIEW))>
  endm
GTK_TREE_VIEW_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_VIEW, GtkTreeViewClass))>
  endm

CALLBACK(GtkTreeViewColumnDropFunc, :ptr, :ptr, :ptr, :ptr, :gpointer)
CALLBACK(GtkTreeViewMappingFunc, :ptr, :ptr, :gpointer)
CALLBACK(GtkTreeViewSearchEqualFunc, :ptr, :sdword, :ptr, :ptr, :gpointer)
CALLBACK(GtkTreeViewRowSeparatorFunc, :ptr, :ptr, :gpointer)

GtkTreeView             struct
parent_instance         GtkWidget <>
GtkTreeView             ends

GtkTreeViewClass        struct
parent_class            GtkWidgetClass <>
row_activated           proc :ptr, :ptr, :ptr
test_expand_row         proc :ptr, :ptr, :ptr
test_collapse_row       proc :ptr, :ptr, :ptr
row_expanded            proc :ptr, :ptr, :ptr
row_collapsed           proc :ptr, :ptr, :ptr
columns_changed         proc :ptr
cursor_changed          proc :ptr
move_cursor             proc :ptr, :GtkMovementStep, :sdword, :gboolean, :gboolean
select_all              proc :ptr
unselect_all            proc :ptr
select_cursor_row       proc :ptr, :gboolean
toggle_cursor_row       proc :ptr
expand_collapse_cursor_row proc :ptr, :gboolean, :gboolean, :gboolean
select_cursor_parent    proc :ptr
start_interactive_search proc :ptr
_reserved               gpointer 16 dup(?)
GtkTreeViewClass        ends

gtk_tree_view_get_type proto

gtk_tree_view_new proto
gtk_tree_view_new_with_model proto :ptr

gtk_tree_view_get_model proto :ptr
gtk_tree_view_set_model proto :ptr, :ptr
gtk_tree_view_get_selection proto :ptr

gtk_tree_view_get_headers_visible proto :ptr
gtk_tree_view_set_headers_visible proto :ptr, :gboolean
gtk_tree_view_columns_autosize proto :ptr
gtk_tree_view_get_headers_clickable proto :ptr
gtk_tree_view_set_headers_clickable proto :ptr, :gboolean
gtk_tree_view_get_activate_on_single_click proto :ptr
gtk_tree_view_set_activate_on_single_click proto :ptr, :gboolean

gtk_tree_view_append_column proto :ptr, :ptr
gtk_tree_view_remove_column proto :ptr, :ptr
gtk_tree_view_insert_column proto :ptr, :ptr, :sdword
gtk_tree_view_insert_column_with_attributes proto :ptr, :sdword, :ptr, :ptr, :vararg
gtk_tree_view_insert_column_with_data_func proto :ptr, :sdword, :ptr, :ptr, :GtkTreeCellDataFunc, :gpointer, :GDestroyNotify

gtk_tree_view_get_n_columns proto :ptr
gtk_tree_view_get_column proto :ptr, :sdword
gtk_tree_view_get_columns proto :ptr
gtk_tree_view_move_column_after proto :ptr, :ptr, :ptr
gtk_tree_view_set_expander_column proto :ptr, :ptr
gtk_tree_view_get_expander_column proto :ptr
gtk_tree_view_set_column_drag_function proto :ptr, :GtkTreeViewColumnDropFunc, :gpointer, :GDestroyNotify

gtk_tree_view_scroll_to_point proto :ptr, :sdword, :sdword
gtk_tree_view_scroll_to_cell proto :ptr, :ptr, :ptr, :gboolean, :real4, :real4
gtk_tree_view_row_activated proto :ptr, :ptr, :ptr
gtk_tree_view_expand_all proto :ptr
gtk_tree_view_collapse_all proto :ptr
gtk_tree_view_expand_to_path proto :ptr, :ptr
gtk_tree_view_expand_row proto :ptr, :ptr, :gboolean
gtk_tree_view_collapse_row proto :ptr, :ptr
gtk_tree_view_map_expanded_rows proto :ptr, :GtkTreeViewMappingFunc, :gpointer
gtk_tree_view_row_expanded proto :ptr, :ptr
gtk_tree_view_set_reorderable proto :ptr, :gboolean
gtk_tree_view_get_reorderable proto :ptr
gtk_tree_view_set_cursor proto :ptr, :ptr, :ptr, :gboolean
gtk_tree_view_set_cursor_on_cell proto :ptr, :ptr, :ptr, :ptr, :gboolean
gtk_tree_view_get_cursor proto :ptr, :ptr, :ptr

gtk_tree_view_get_path_at_pos proto :ptr, :sdword, :sdword, :ptr, :ptr, :ptr, :ptr
gtk_tree_view_get_cell_area proto :ptr, :ptr, :ptr, :ptr
gtk_tree_view_get_background_area proto :ptr, :ptr, :ptr, :ptr
gtk_tree_view_get_visible_rect proto :ptr, :ptr
gtk_tree_view_get_visible_range proto :ptr, :ptr, :ptr
gtk_tree_view_is_blank_at_pos proto :ptr, :sdword, :sdword, :ptr, :ptr, :ptr, :ptr


gtk_tree_view_enable_model_drag_source proto :ptr, :GdkModifierType, :ptr, :GdkDragAction
gtk_tree_view_enable_model_drag_dest proto :ptr, :ptr, :GdkDragAction
gtk_tree_view_unset_rows_drag_source proto :ptr
gtk_tree_view_unset_rows_drag_dest proto :ptr



gtk_tree_view_set_drag_dest_row proto :ptr, :ptr, :GtkTreeViewDropPosition
gtk_tree_view_get_drag_dest_row proto :ptr, :ptr, :ptr
gtk_tree_view_get_dest_row_at_pos proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_create_row_drag_icon proto :ptr, :ptr


gtk_tree_view_set_enable_search proto :ptr, :gboolean
gtk_tree_view_get_enable_search proto :ptr
gtk_tree_view_get_search_column proto :ptr
gtk_tree_view_set_search_column proto :ptr, :sdword
gtk_tree_view_get_search_equal_func proto :ptr
gtk_tree_view_set_search_equal_func proto :ptr, :GtkTreeViewSearchEqualFunc, :gpointer, :GDestroyNotify

gtk_tree_view_get_search_entry proto :ptr
gtk_tree_view_set_search_entry proto :ptr, :ptr


gtk_tree_view_convert_widget_to_tree_coords proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_convert_tree_to_widget_coords proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_convert_widget_to_bin_window_coords proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_convert_bin_window_to_widget_coords proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_convert_tree_to_bin_window_coords proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_tree_view_convert_bin_window_to_tree_coords proto :ptr, :sdword, :sdword, :ptr, :ptr

gtk_tree_view_set_fixed_height_mode proto :ptr, :gboolean
gtk_tree_view_get_fixed_height_mode proto :ptr
gtk_tree_view_set_hover_selection proto :ptr, :gboolean
gtk_tree_view_get_hover_selection proto :ptr
gtk_tree_view_set_hover_expand proto :ptr, :gboolean
gtk_tree_view_get_hover_expand proto :ptr
gtk_tree_view_set_rubber_banding proto :ptr, :gboolean
gtk_tree_view_get_rubber_banding proto :ptr

gtk_tree_view_is_rubber_banding_active proto :ptr

gtk_tree_view_get_row_separator_func proto :ptr
gtk_tree_view_set_row_separator_func proto :ptr, :GtkTreeViewRowSeparatorFunc, :gpointer, :GDestroyNotify

gtk_tree_view_get_grid_lines proto :ptr
gtk_tree_view_set_grid_lines proto :ptr, :GtkTreeViewGridLines
gtk_tree_view_get_enable_tree_lines proto :ptr
gtk_tree_view_set_enable_tree_lines proto :ptr, :gboolean
gtk_tree_view_set_show_expanders proto :ptr, :gboolean
gtk_tree_view_get_show_expanders proto :ptr
gtk_tree_view_set_level_indentation proto :ptr, :sdword
gtk_tree_view_get_level_indentation proto :ptr

gtk_tree_view_set_tooltip_row proto :ptr, :ptr, :ptr
gtk_tree_view_set_tooltip_cell proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_tree_view_get_tooltip_context proto :ptr, :sdword, :sdword, :gboolean, :ptr, :ptr, :ptr
gtk_tree_view_set_tooltip_column proto :ptr, :sdword
gtk_tree_view_get_tooltip_column proto :ptr

endif

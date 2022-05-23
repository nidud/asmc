ifndef __GTK_GRID_LAYOUT_H__
define __GTK_GRID_LAYOUT_H__

include gtk/gtklayoutmanager.inc

define GTK_TYPE_GRID_LAYOUT <gtk_grid_layout_get_type>
define GTK_TYPE_GRID_LAYOUT_CHILD <gtk_grid_layout_child_get_type>

gtk_grid_layout_new proto

gtk_grid_layout_set_row_homogeneous proto :ptr, :gboolean
gtk_grid_layout_get_row_homogeneous proto :ptr
gtk_grid_layout_set_row_spacing proto :ptr, :guint
gtk_grid_layout_get_row_spacing proto :ptr
gtk_grid_layout_set_column_homogeneous proto :ptr, :gboolean
gtk_grid_layout_get_column_homogeneous proto :ptr
gtk_grid_layout_set_column_spacing proto :ptr, :guint
gtk_grid_layout_get_column_spacing proto :ptr
gtk_grid_layout_set_row_baseline_position proto :ptr, :sdword, :GtkBaselinePosition
gtk_grid_layout_get_row_baseline_position proto :ptr, :sdword
gtk_grid_layout_set_baseline_row proto :ptr, :sdword
gtk_grid_layout_get_baseline_row proto :ptr

gtk_grid_layout_child_set_row proto :ptr, :sdword
gtk_grid_layout_child_get_row proto :ptr
gtk_grid_layout_child_set_column proto :ptr, :sdword
gtk_grid_layout_child_get_column proto :ptr
gtk_grid_layout_child_set_column_span proto :ptr, :sdword
gtk_grid_layout_child_get_column_span proto :ptr
gtk_grid_layout_child_set_row_span proto :ptr, :sdword
gtk_grid_layout_child_get_row_span proto :ptr

endif

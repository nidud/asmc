ifndef __GTK_GRID_H__
define __GTK_GRID_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_GRID <gtk_grid_get_type ()>
GTK_GRID macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_GRID, GtkGrid))>
  endm
GTK_GRID_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_GRID, GtkGridClass))>
  endm
GTK_IS_GRID macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_GRID))>
  endm
GTK_IS_GRID_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_GRID))>
  endm
GTK_GRID_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_GRID, GtkGridClass))>
  endm

_GtkGrid                struct
parent_instance         GtkWidget <>
_GtkGrid                ends
GtkGrid                 typedef _GtkGrid

_GtkGridClass           struct
parent_class            GtkWidgetClass <>
padding                 gpointer 8 dup(?)
_GtkGridClass           ends
GtkGridClass            typedef _GtkGridClass

gtk_grid_get_type proto
gtk_grid_new proto
gtk_grid_attach proto :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
gtk_grid_attach_next_to proto :ptr, :ptr, :ptr, :GtkPositionType, :sdword, :sdword
gtk_grid_get_child_at proto :ptr, :sdword, :sdword
gtk_grid_remove proto :ptr, :ptr

gtk_grid_insert_row proto :ptr, :sdword
gtk_grid_insert_column proto :ptr, :sdword
gtk_grid_remove_row proto :ptr, :sdword
gtk_grid_remove_column proto :ptr, :sdword
gtk_grid_insert_next_to proto :ptr, :ptr, :GtkPositionType
gtk_grid_set_row_homogeneous proto :ptr, :gboolean
gtk_grid_get_row_homogeneous proto :ptr
gtk_grid_set_row_spacing proto :ptr, :guint
gtk_grid_get_row_spacing proto :ptr
gtk_grid_set_column_homogeneous proto :ptr, :gboolean
gtk_grid_get_column_homogeneous proto :ptr
gtk_grid_set_column_spacing proto :ptr, :guint
gtk_grid_get_column_spacing proto :ptr
gtk_grid_set_row_baseline_position proto :ptr, :sdword, :GtkBaselinePosition
gtk_grid_get_row_baseline_position proto :ptr, :sdword
gtk_grid_set_baseline_row proto :ptr, :sdword
gtk_grid_get_baseline_row proto :ptr

gtk_grid_query_child proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

endif

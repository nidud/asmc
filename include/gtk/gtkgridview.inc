ifndef __GTK_GRID_VIEW_H__
define __GTK_GRID_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtklistbase.inc

define GTK_TYPE_GRID_VIEW <gtk_grid_view_get_type ()>
GTK_GRID_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_GRID_VIEW, GtkGridView))>
  endm
GTK_GRID_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_GRID_VIEW, GtkGridViewClass))>
  endm
GTK_IS_GRID_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_GRID_VIEW))>
  endm
GTK_IS_GRID_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_GRID_VIEW))>
  endm
GTK_GRID_VIEW_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_GRID_VIEW, GtkGridViewClass))>
  endm

;GtkGridView             typedef _GtkGridView
;GtkGridViewClass        typedef _GtkGridViewClass

gtk_grid_view_get_type proto
gtk_grid_view_new proto :ptr, :ptr

gtk_grid_view_get_model proto :ptr
gtk_grid_view_set_model proto :ptr, :ptr
gtk_grid_view_set_factory proto :ptr, :ptr
gtk_grid_view_get_factory proto :ptr
gtk_grid_view_get_min_columns proto :ptr
gtk_grid_view_set_min_columns proto :ptr, :guint
gtk_grid_view_get_max_columns proto :ptr
gtk_grid_view_set_max_columns proto :ptr, :guint
gtk_grid_view_set_enable_rubberband proto :ptr, :gboolean
gtk_grid_view_get_enable_rubberband proto :ptr

gtk_grid_view_set_single_click_activate proto :ptr, :gboolean
gtk_grid_view_get_single_click_activate proto :ptr

endif

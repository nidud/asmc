ifndef __GTK_CELL_VIEW_H__
define __GTK_CELL_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtkcellareacontext.inc
include gtk/gtktreemodel.inc

define GTK_TYPE_CELL_VIEW <gtk_cell_view_get_type ()>
GTK_CELL_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_VIEW, GtkCellView))>
  endm
GTK_IS_CELL_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_VIEW))>
  endm

;GtkCellView             typedef _GtkCellView

gtk_cell_view_get_type proto
gtk_cell_view_new proto
gtk_cell_view_new_with_context proto :ptr, :ptr
gtk_cell_view_new_with_text proto :ptr
gtk_cell_view_new_with_markup proto :ptr
gtk_cell_view_new_with_texture proto :ptr
gtk_cell_view_set_model proto :ptr, :ptr
gtk_cell_view_get_model proto :ptr
gtk_cell_view_set_displayed_row proto :ptr, :ptr
gtk_cell_view_get_displayed_row proto :ptr
gtk_cell_view_get_draw_sensitive proto :ptr
gtk_cell_view_set_draw_sensitive proto :ptr, :gboolean
gtk_cell_view_get_fit_model proto :ptr
gtk_cell_view_set_fit_model proto :ptr, :gboolean

endif

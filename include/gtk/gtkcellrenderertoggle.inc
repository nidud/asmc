ifndef __GTK_CELL_RENDERER_TOGGLE_H__
define __GTK_CELL_RENDERER_TOGGLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

define GTK_TYPE_CELL_RENDERER_TOGGLE	<gtk_cell_renderer_toggle_get_type ()>
GTK_CELL_RENDERER_TOGGLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_TOGGLE, GtkCellRendererToggle))>
  endm
GTK_IS_CELL_RENDERER_TOGGLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_TOGGLE))>
  endm

;GtkCellRendererToggle	 typedef _GtkCellRendererToggle

gtk_cell_renderer_toggle_get_type proto
gtk_cell_renderer_toggle_new proto
gtk_cell_renderer_toggle_get_radio proto :ptr
gtk_cell_renderer_toggle_set_radio proto :ptr, :gboolean
gtk_cell_renderer_toggle_get_active proto :ptr
gtk_cell_renderer_toggle_set_active proto :ptr, :gboolean
gtk_cell_renderer_toggle_get_activatable proto :ptr
gtk_cell_renderer_toggle_set_activatable proto :ptr, :gboolean

endif

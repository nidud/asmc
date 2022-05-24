ifndef __GTK_CELL_RENDERER_COMBO_H__
define __GTK_CELL_RENDERER_COMBO_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc
include gtk/gtkcellrenderertext.inc

define GTK_TYPE_CELL_RENDERER_COMBO	<gtk_cell_renderer_combo_get_type ()>
GTK_CELL_RENDERER_COMBO macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_COMBO, GtkCellRendererCombo))>
  endm
GTK_IS_CELL_RENDERER_COMBO macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_COMBO))>
  endm

;GtkCellRendererCombo	 typedef _GtkCellRendererCombo

gtk_cell_renderer_combo_get_type proto
gtk_cell_renderer_combo_new proto

endif

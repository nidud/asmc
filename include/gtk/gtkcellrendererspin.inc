ifndef __GTK_CELL_RENDERER_SPIN_H__
define __GTK_CELL_RENDERER_SPIN_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderertext.inc

define GTK_TYPE_CELL_RENDERER_SPIN	<gtk_cell_renderer_spin_get_type ()>
GTK_CELL_RENDERER_SPIN macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_SPIN, GtkCellRendererSpin))>
  endm
GTK_IS_CELL_RENDERER_SPIN macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_SPIN))>
  endm

gtk_cell_renderer_spin_get_type proto
gtk_cell_renderer_spin_new proto

endif

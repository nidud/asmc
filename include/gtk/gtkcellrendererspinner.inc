ifndef __GTK_CELL_RENDERER_SPINNER_H__
define __GTK_CELL_RENDERER_SPINNER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

define GTK_TYPE_CELL_RENDERER_SPINNER <gtk_cell_renderer_spinner_get_type ()>
GTK_CELL_RENDERER_SPINNER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_SPINNER, GtkCellRendererSpinner))>
  endm
GTK_IS_CELL_RENDERER_SPINNER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_SPINNER))>
  endm

;GtkCellRendererSpinner  typedef _GtkCellRendererSpinner

gtk_cell_renderer_spinner_get_type proto
gtk_cell_renderer_spinner_new proto

endif

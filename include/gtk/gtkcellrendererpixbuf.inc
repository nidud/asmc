ifndef __GTK_CELL_RENDERER_PIXBUF_H__
define __GTK_CELL_RENDERER_PIXBUF_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

define GTK_TYPE_CELL_RENDERER_PIXBUF	<gtk_cell_renderer_pixbuf_get_type ()>
GTK_CELL_RENDERER_PIXBUF macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_PIXBUF, GtkCellRendererPixbuf))>
  endm
GTK_IS_CELL_RENDERER_PIXBUF macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_PIXBUF))>
  endm

;GtkCellRendererPixbuf	 typedef _GtkCellRendererPixbuf

gtk_cell_renderer_pixbuf_get_type proto
gtk_cell_renderer_pixbuf_new proto

endif

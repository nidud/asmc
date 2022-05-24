ifndef __GTK_CELL_RENDERER_TEXT_H__
define __GTK_CELL_RENDERER_TEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

define GTK_TYPE_CELL_RENDERER_TEXT	<gtk_cell_renderer_text_get_type ()>
GTK_CELL_RENDERER_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_TEXT, GtkCellRendererText))>
  endm
GTK_CELL_RENDERER_TEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_TEXT, GtkCellRendererTextClass))>
  endm
GTK_IS_CELL_RENDERER_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_TEXT))>
  endm
GTK_IS_CELL_RENDERER_TEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_TEXT))>
  endm
GTK_CELL_RENDERER_TEXT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_TEXT, GtkCellRendererTextClass))>
  endm

_GtkCellRendererText	struct
parent			GtkCellRenderer <>
_GtkCellRendererText	ends
GtkCellRendererText	typedef _GtkCellRendererText

_GtkCellRendererTextClass struct
parent_class		GtkCellRendererClass <>
edited			proc :ptr, :ptr, :ptr
padding			gpointer 8 dup(?)
_GtkCellRendererTextClass ends
GtkCellRendererTextClass typedef _GtkCellRendererTextClass

gtk_cell_renderer_text_get_type proto
gtk_cell_renderer_text_new proto
gtk_cell_renderer_text_set_fixed_height_from_font proto :ptr, :sdword

endif

ifndef __GTK_CELL_RENDERER_TEXT_H__
__GTK_CELL_RENDERER_TEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_TEXT equ <gtk_cell_renderer_text_get_type>
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

GtkCellRendererText	STRUC
parent			GtkCellRenderer <>
priv			ptr_t ?
GtkCellRendererText	ENDS

GtkCellRendererTextClass STRUC
parent_class		GtkCellRendererClass <>
edited			proc :ptr GtkCellRendererText, :ptr gchar, :ptr gchar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererTextClass ENDS

;GType
gtk_cell_renderer_text_get_type proto __cdecl
;GtkCellRenderer
gtk_cell_renderer_text_new proto __cdecl

;void
gtk_cell_renderer_text_set_fixed_height_from_font proto __cdecl \
	      renderer: ptr GtkCellRendererText,
	number_of_rows: gint

G_END_DECLS

endif

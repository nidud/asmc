ifndef __GTK_CELL_RENDERER_SPINNER_H__
__GTK_CELL_RENDERER_SPINNER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_SPINNER equ <gtk_cell_renderer_spinner_get_type>
GTK_CELL_RENDERER_SPINNER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_SPINNER, GtkCellRendererSpinner))>
	endm
GTK_CELL_RENDERER_SPINNER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_SPINNER, GtkCellRendererSpinnerClass))>
	endm
GTK_IS_CELL_RENDERER_SPINNER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_SPINNER))>
	endm
GTK_IS_CELL_RENDERER_SPINNER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_SPINNER))>
	endm
GTK_CELL_RENDERER_SPINNER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_SPINNER, GtkCellRendererSpinnerClass))>
	endm

GtkCellRendererSpinner	STRUC
parent			GtkCellRenderer <>
priv			ptr_t ?
GtkCellRendererSpinner	ENDS

GtkCellRendererSpinnerClass STRUC
parent_class		GtkCellRendererClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererSpinnerClass ENDS

;GType
gtk_cell_renderer_spinner_get_type proto __cdecl
;GtkCellRenderer
gtk_cell_renderer_spinner_new proto __cdecl

G_END_DECLS

endif

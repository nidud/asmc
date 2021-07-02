ifndef __GTK_CELL_RENDERER_PROGRESS_H__
__GTK_CELL_RENDERER_PROGRESS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_PROGRESS equ <gtk_cell_renderer_progress_get_type>
GTK_CELL_RENDERER_PROGRESS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_PROGRESS, GtkCellRendererProgress))>
	endm
GTK_CELL_RENDERER_PROGRESS_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_PROGRESS, GtkCellRendererProgressClass))>
	endm
GTK_IS_CELL_RENDERER_PROGRESS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_PROGRESS))>
	endm
GTK_IS_CELL_RENDERER_PROGRESS_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_PROGRESS))>
	endm
GTK_CELL_RENDERER_PROGRESS_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_PROGRESS, GtkCellRendererProgressClass))>
	endm

GtkCellRendererProgress STRUC
parent_instance		GtkCellRenderer <>
priv			ptr_t ?
GtkCellRendererProgress ENDS

GtkCellRendererProgressClass STRUC
parent_class		GtkCellRendererClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererProgressClass ENDS

;GType
gtk_cell_renderer_progress_get_type proto __cdecl
;GtkCellRenderer*
gtk_cell_renderer_progress_new proto __cdecl

G_END_DECLS

endif

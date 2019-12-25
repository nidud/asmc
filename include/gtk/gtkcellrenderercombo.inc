ifndef __GTK_CELL_RENDERER_COMBO_H__
__GTK_CELL_RENDERER_COMBO_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc
include gtk/gtkcellrenderertext.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_COMBO equ <gtk_cell_renderer_combo_get_type>
GTK_CELL_RENDERER_COMBO macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_COMBO, GtkCellRendererCombo))>
	endm
GTK_CELL_RENDERER_COMBO_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_COMBO, GtkCellRendererComboClass))>
	endm
GTK_IS_CELL_RENDERER_COMBO macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_COMBO))>
	endm
GTK_IS_CELL_RENDERER_COMBO_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_COMBO))>
	endm
GTK_CELL_RENDERER_COMBO_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_COMBO, GtkCellRendererTextClass))>
	endm

GtkCellRendererCombo	STRUC
parent			GtkCellRendererText <>
priv			ptr_t ?
GtkCellRendererCombo	ENDS

GtkCellRendererComboClass STRUC
parent			GtkCellRendererTextClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererComboClass ENDS

;GType
gtk_cell_renderer_combo_get_type proto __cdecl
;GtkCellRenderer
gtk_cell_renderer_combo_new proto __cdecl

G_END_DECLS

endif

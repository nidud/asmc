ifndef __GTK_CELL_RENDERER_TOGGLE_H__
__GTK_CELL_RENDERER_TOGGLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_RENDERER_TOGGLE equ <gtk_cell_renderer_toggle_get_type>
GTK_CELL_RENDERER_TOGGLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_TOGGLE, GtkCellRendererToggle))>
	endm
GTK_CELL_RENDERER_TOGGLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER_TOGGLE, GtkCellRendererToggleClass))>
	endm
GTK_IS_CELL_RENDERER_TOGGLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_TOGGLE))>
	endm
GTK_IS_CELL_RENDERER_TOGGLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER_TOGGLE))>
	endm
GTK_CELL_RENDERER_TOGGLE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER_TOGGLE, GtkCellRendererToggleClass))>
	endm

GtkCellRendererToggle	STRUC
parent			GtkCellRenderer <>
priv			ptr_t ?
GtkCellRendererToggle	ENDS

GtkCellRendererToggleClass STRUC
parent_class		GtkCellRendererClass <>
toggled			proc :ptr GtkCellRendererToggle, :ptr gchar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererToggleClass ENDS

;GType
gtk_cell_renderer_toggle_get_type proto __cdecl
;GtkCellRenderer
gtk_cell_renderer_toggle_new proto __cdecl

;gboolean
gtk_cell_renderer_toggle_get_radio proto __cdecl \
		toggle: ptr GtkCellRendererToggle

;void
gtk_cell_renderer_toggle_set_radio proto __cdecl \
		toggle: ptr GtkCellRendererToggle,
		 radio: gboolean


;gboolean
gtk_cell_renderer_toggle_get_active proto __cdecl \
		toggle: ptr GtkCellRendererToggle

;void
gtk_cell_renderer_toggle_set_active proto __cdecl \
		toggle: ptr GtkCellRendererToggle,
	       setting: gboolean


;gboolean
gtk_cell_renderer_toggle_get_activatable proto __cdecl \
		toggle: ptr GtkCellRendererToggle

;void
gtk_cell_renderer_toggle_set_activatable proto __cdecl \
		toggle: ptr GtkCellRendererToggle,
	       setting: gboolean

G_END_DECLS

endif

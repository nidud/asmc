ifndef __GTK_CELL_AREA_BOX_H__
__GTK_CELL_AREA_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellarea.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_AREA_BOX equ <gtk_cell_area_box_get_type>
GTK_CELL_AREA_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA_BOX, GtkCellAreaBox))>
	endm
GTK_CELL_AREA_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_AREA_BOX, GtkCellAreaBoxClass))>
	endm
GTK_IS_CELL_AREA_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA_BOX))>
	endm
GTK_IS_CELL_AREA_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_AREA_BOX))>
	endm
GTK_CELL_AREA_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_AREA_BOX, GtkCellAreaBoxClass))>
	endm

GtkCellAreaBox		STRUC
parent_instance		GtkCellArea <>
priv			ptr_t ?
GtkCellAreaBox		ENDS

GtkCellAreaBoxClass	STRUC
parent_class		GtkCellAreaClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellAreaBoxClass	ENDS

;GType
gtk_cell_area_box_get_type proto __cdecl

;GtkCellArea
gtk_cell_area_box_new proto __cdecl
;void
gtk_cell_area_box_pack_start proto __cdecl \
		   box: ptr GtkCellAreaBox,
	      renderer: ptr GtkCellRenderer,
		expand: gboolean,
		_align: gboolean,
		 fixed: gboolean

;void
gtk_cell_area_box_pack_end proto __cdecl \
		   box: ptr GtkCellAreaBox,
	      renderer: ptr GtkCellRenderer,
		expand: gboolean,
		_align: gboolean,
		 fixed: gboolean

;gint
gtk_cell_area_box_get_spacing proto __cdecl \
		   box: ptr GtkCellAreaBox

;void
gtk_cell_area_box_set_spacing proto __cdecl \
		   box: ptr GtkCellAreaBox,
	       spacing: gint


;_gtk_cell_area_box_group_visible(GtkCellAreaBox
_gtk_cell_area_box_group_visible proto __cdecl

G_END_DECLS

endif

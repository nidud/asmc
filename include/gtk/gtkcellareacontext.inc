ifndef __GTK_CELL_AREA_CONTEXT_H__
__GTK_CELL_AREA_CONTEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellarea.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_AREA_CONTEXT equ <gtk_cell_area_context_get_type>
GTK_CELL_AREA_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContext))>
	endm
GTK_CELL_AREA_CONTEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContextClass))>
	endm
GTK_IS_CELL_AREA_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA_CONTEXT))>
	endm
GTK_IS_CELL_AREA_CONTEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_AREA_CONTEXT))>
	endm
GTK_CELL_AREA_CONTEXT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContextClass))>
	endm

GtkCellAreaContext	STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkCellAreaContext	ENDS

GtkCellAreaContextClass STRUC
parent_class		GObjectClass <>
allocate		proc :ptr GtkCellAreaContext, :gint, :gint
reset			proc :ptr GtkCellAreaContext
get_preferred_height_for_width proc :ptr GtkCellAreaContext, :gint, :ptr gint, :ptr gint
get_preferred_width_for_height proc :ptr GtkCellAreaContext, :gint, :ptr gint, :ptr gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
GtkCellAreaContextClass ENDS

;GType
gtk_cell_area_context_get_type proto __cdecl

;GtkCellArea
gtk_cell_area_context_get_area proto __cdecl \
	       context: ptr GtkCellAreaContext

;void
gtk_cell_area_context_allocate proto __cdecl \
	       context: ptr GtkCellAreaContext,
		 width: gint,
		height: gint

;void
gtk_cell_area_context_reset proto __cdecl \
	       context: ptr GtkCellAreaContext


;void
gtk_cell_area_context_get_preferred_width proto __cdecl \
	       context: ptr GtkCellAreaContext,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_cell_area_context_get_preferred_height proto __cdecl \
	       context: ptr GtkCellAreaContext,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_cell_area_context_get_preferred_height_for_width proto __cdecl \
	       context: ptr GtkCellAreaContext,
		 width: gint,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_cell_area_context_get_preferred_width_for_height proto __cdecl \
	       context: ptr GtkCellAreaContext,
		height: gint,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_cell_area_context_get_allocation proto __cdecl \
	       context: ptr GtkCellAreaContext,
		 width: ptr gint,
		height: ptr gint

;void
gtk_cell_area_context_push_preferred_width proto __cdecl \
	       context: ptr GtkCellAreaContext,
	 minimum_width: gint,
	 natural_width: gint

;void
gtk_cell_area_context_push_preferred_height proto __cdecl \
	       context: ptr GtkCellAreaContext,
	minimum_height: gint,
	natural_height: gint

G_END_DECLS

endif

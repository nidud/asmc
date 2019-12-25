ifndef __GTK_GRID_H__
__GTK_GRID_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_GRID equ <gtk_grid_get_type>
GTK_GRID macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_GRID, GtkGrid))>
	endm
GTK_GRID_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_GRID, GtkGridClass))>
	endm
GTK_IS_GRID macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_GRID))>
	endm
GTK_IS_GRID_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_GRID))>
	endm
GTK_GRID_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_GRID, GtkGridClass))>
	endm


GtkGrid			STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkGrid			ENDS

GtkGridClass		STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkGridClass		ENDS

;GType
gtk_grid_get_type proto __cdecl
;GtkWidget*
gtk_grid_new proto __cdecl
;void
gtk_grid_attach proto __cdecl \
		  grid: ptr GtkGrid,
		 child: ptr GtkWidget,
		  left: gint,
		   top: gint,
		 width: gint,
		height: gint

;void
gtk_grid_attach_next_to proto __cdecl \
		  grid: ptr GtkGrid,
		 child: ptr GtkWidget,
	       sibling: ptr GtkWidget,
		  side: GtkPositionType,
		 width: gint,
		height: gint

;GtkWidget
gtk_grid_get_child_at proto __cdecl \
		  grid: ptr GtkGrid,
		  left: gint,
		   top: gint

;void
gtk_grid_insert_row proto __cdecl \
		  grid: ptr GtkGrid,
	      position: gint

;void
gtk_grid_insert_column proto __cdecl \
		  grid: ptr GtkGrid,
	      position: gint

;void
gtk_grid_remove_row proto __cdecl \
		  grid: ptr GtkGrid,
	      position: gint

;void
gtk_grid_remove_column proto __cdecl \
		  grid: ptr GtkGrid,
	      position: gint

;void
gtk_grid_insert_next_to proto __cdecl \
		  grid: ptr GtkGrid,
	       sibling: ptr GtkWidget,
		  side: GtkPositionType

;void
gtk_grid_set_row_homogeneous proto __cdecl \
		  grid: ptr GtkGrid,
	   homogeneous: gboolean

;gboolean
gtk_grid_get_row_homogeneous proto __cdecl \
		  grid: ptr GtkGrid

;void
gtk_grid_set_row_spacing proto __cdecl \
		  grid: ptr GtkGrid,
	       spacing: guint

;guint
gtk_grid_get_row_spacing proto __cdecl \
		  grid: ptr GtkGrid

;void
gtk_grid_set_column_homogeneous proto __cdecl \
		  grid: ptr GtkGrid,
	   homogeneous: gboolean

;gboolean
gtk_grid_get_column_homogeneous proto __cdecl \
		  grid: ptr GtkGrid

;void
gtk_grid_set_column_spacing proto __cdecl \
		  grid: ptr GtkGrid,
	       spacing: guint

;guint
gtk_grid_get_column_spacing proto __cdecl \
		  grid: ptr GtkGrid

;void
gtk_grid_set_row_baseline_position proto __cdecl \
		  grid: ptr GtkGrid,
		   row: gint,
		   pos: GtkBaselinePosition

;GtkBaselinePosition
gtk_grid_get_row_baseline_position proto __cdecl \
		  grid: ptr GtkGrid,
		   row: gint

;void
gtk_grid_set_baseline_row proto __cdecl \
		  grid: ptr GtkGrid,
		   row: gint

;gint
gtk_grid_get_baseline_row proto __cdecl \
		  grid: ptr GtkGrid


G_END_DECLS

endif

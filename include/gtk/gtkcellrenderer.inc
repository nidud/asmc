ifndef __GTK_CELL_RENDERER_H__
__GTK_CELL_RENDERER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcelleditable.inc

G_BEGIN_DECLS

.enum GtkCellRendererState {
  GTK_CELL_RENDERER_SELECTED	= 1 shl 0,
  GTK_CELL_RENDERER_PRELIT	= 1 shl 1,
  GTK_CELL_RENDERER_INSENSITIVE = 1 shl 2,
  GTK_CELL_RENDERER_SORTED	= 1 shl 3,
  GTK_CELL_RENDERER_FOCUSED	= 1 shl 4,
  GTK_CELL_RENDERER_EXPANDABLE	= 1 shl 5,
  GTK_CELL_RENDERER_EXPANDED	= 1 shl 6
}

.enum GtkCellRendererMode {
  GTK_CELL_RENDERER_MODE_INERT,
  GTK_CELL_RENDERER_MODE_ACTIVATABLE,
  GTK_CELL_RENDERER_MODE_EDITABLE
}

GTK_TYPE_CELL_RENDERER	equ <gtk_cell_renderer_get_type>
GTK_CELL_RENDERER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER, GtkCellRenderer))>
	endm
GTK_CELL_RENDERER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_RENDERER, GtkCellRendererClass))>
	endm
GTK_IS_CELL_RENDERER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER))>
	endm
GTK_IS_CELL_RENDERER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_RENDERER))>
	endm
GTK_CELL_RENDERER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_RENDERER, GtkCellRendererClass))>
	endm

GtkCellRenderer		STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr_t ?
GtkCellRenderer		ENDS

GtkCellRendererClass	STRUC
parent_class		GInitiallyUnownedClass <>
get_request_mode	proc :ptr GtkCellRenderer
get_preferred_width	proc :ptr GtkCellRenderer,  :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_height_for_width proc :ptr GtkCellRenderer, :ptr GtkWidget, :gint, :ptr gint, :ptr gint
get_preferred_height	proc :ptr GtkCellRenderer, :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_width_for_height proc :ptr GtkCellRenderer, :ptr GtkWidget, :gint, :ptr gint, :ptr gint
get_aligned_area	proc :ptr GtkCellRenderer, :ptr GtkWidget, :GtkCellRendererState, :ptr GdkRectangle, :ptr GdkRectangle
get_size		proc :ptr GtkCellRenderer, :ptr GtkWidget, :ptr GdkRectangle, :ptr gint, :ptr gint, :ptr gint, :ptr gint
render			proc :ptr GtkCellRenderer, :ptr cairo_t, :ptr GtkWidget, :ptr GdkRectangle, :ptr GdkRectangle, :GtkCellRendererState
activate		proc :ptr GtkCellRenderer, :ptr GdkEvent, :ptr GtkWidget, :ptr gchar, :ptr GdkRectangle, :ptr GdkRectangle, :GtkCellRendererState
start_editing		proc :ptr GtkCellRenderer, :ptr GdkEvent, :ptr GtkWidget, :ptr gchar, :ptr GdkRectangle, :ptr GdkRectangle, :GtkCellRendererState
editing_canceled	proc :ptr GtkCellRenderer
editing_started		proc :ptr GtkCellRenderer, :ptr GtkCellEditable, :ptr gchar
priv			ptr_t ?
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellRendererClass	ENDS

;GType
gtk_cell_renderer_get_type proto __cdecl

;GtkSizeRequestMode
gtk_cell_renderer_get_request_mode proto __cdecl \
		  cell: ptr GtkCellRenderer

;void
gtk_cell_renderer_get_preferred_width proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
	  minimum_size: ptr gint,
	  natural_size: ptr gint

;void
gtk_cell_renderer_get_preferred_height_for_width proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
		 width: gint,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_cell_renderer_get_preferred_height proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
	  minimum_size: ptr gint,
	  natural_size: ptr gint

;void
gtk_cell_renderer_get_preferred_width_for_height proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
		height: gint,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_cell_renderer_get_preferred_size proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
	  minimum_size: ptr GtkRequisition,
	  natural_size: ptr GtkRequisition

;void
gtk_cell_renderer_get_aligned_area proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
		 flags: GtkCellRendererState,
	     cell_area: ptr GdkRectangle,
	  aligned_area: ptr GdkRectangle


;void
gtk_cell_renderer_get_size proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
	     cell_area: ptr GdkRectangle,
	      x_offset: ptr gint,
	      y_offset: ptr gint,
		 width: ptr gint,
		height: ptr gint

;void
gtk_cell_renderer_render proto __cdecl \
		  cell: ptr GtkCellRenderer,
		    cr: ptr cairo_t,
		widget: ptr GtkWidget,
       background_area: ptr GdkRectangle,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState

;gboolean
gtk_cell_renderer_activate proto __cdecl \
		  cell: ptr GtkCellRenderer,
		 event: ptr GdkEvent,
		widget: ptr GtkWidget,
		  path: ptr gchar,
       background_area: ptr GdkRectangle,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState

;GtkCellEditable
gtk_cell_renderer_start_editing proto __cdecl \
		  cell: ptr GtkCellRenderer,
		 event: ptr GdkEvent,
		widget: ptr GtkWidget,
		  path: ptr gchar,
       background_area: ptr GdkRectangle,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState


;void
gtk_cell_renderer_set_fixed_size proto __cdecl \
		  cell: ptr GtkCellRenderer,
		 width: gint,
		height: gint

;void
gtk_cell_renderer_get_fixed_size proto __cdecl \
		  cell: ptr GtkCellRenderer,
		 width: ptr gint,
		height: ptr gint


;void
gtk_cell_renderer_set_alignment proto __cdecl \
		  cell: ptr GtkCellRenderer,
		xalign: gfloat,
		yalign: gfloat

;void
gtk_cell_renderer_get_alignment proto __cdecl \
		  cell: ptr GtkCellRenderer,
		xalign: ptr gfloat,
		yalign: ptr gfloat


;void
gtk_cell_renderer_set_padding proto __cdecl \
		  cell: ptr GtkCellRenderer,
		  xpad: gint,
		  ypad: gint

;void
gtk_cell_renderer_get_padding proto __cdecl \
		  cell: ptr GtkCellRenderer,
		  xpad: ptr gint,
		  ypad: ptr gint


;void
gtk_cell_renderer_set_visible proto __cdecl \
		  cell: ptr GtkCellRenderer,
	       visible: gboolean

;gboolean
gtk_cell_renderer_get_visible proto __cdecl \
		  cell: ptr GtkCellRenderer


;void
gtk_cell_renderer_set_sensitive proto __cdecl \
		  cell: ptr GtkCellRenderer,
	     sensitive: gboolean

;gboolean
gtk_cell_renderer_get_sensitive proto __cdecl \
		  cell: ptr GtkCellRenderer


;gboolean
gtk_cell_renderer_is_activatable proto __cdecl \
		  cell: ptr GtkCellRenderer


;void
gtk_cell_renderer_stop_editing proto __cdecl \
		  cell: ptr GtkCellRenderer,
	      canceled: gboolean



;void
_gtk_cell_renderer_calc_offset proto __cdecl \
		  cell: ptr GtkCellRenderer,
	     cell_area: ptr GdkRectangle,
	     direction: GtkTextDirection,
		 width: gint,
		height: gint,
	      x_offset: ptr gint,
	      y_offset: ptr gint


;GtkStateFlags
gtk_cell_renderer_get_state proto __cdecl \
		  cell: ptr GtkCellRenderer,
		widget: ptr GtkWidget,
	    cell_state: GtkCellRendererState


;void
gtk_cell_renderer_class_set_accessible_type proto __cdecl \
	renderer_class: ptr GtkCellRendererClass,
		  type: GType

;GType
_gtk_cell_renderer_get_accessible_type proto __cdecl \
	      renderer: ptr GtkCellRenderer

G_END_DECLS

endif

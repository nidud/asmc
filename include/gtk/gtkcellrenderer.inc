ifndef __GTK_CELL_RENDERER_H__
define __GTK_CELL_RENDERER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcelleditable.inc

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

define GTK_TYPE_CELL_RENDERER	<gtk_cell_renderer_get_type ()>
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

GtkCellRenderer		struct
parent_instance		GInitiallyUnowned <>
priv			ptr GtkCellRendererPrivate ?
GtkCellRenderer		ends

GtkCellRendererClass	struct
parent_class		GInitiallyUnownedClass <>
get_request_mode	proc :ptr
get_preferred_width	proc :ptr, :ptr, :ptr, :ptr
get_preferred_height_for_width proc :ptr, :ptr, :sdword, :ptr, :ptr
get_preferred_height	proc :ptr, :ptr, :ptr, :ptr
get_preferred_width_for_height proc :ptr, :ptr, :sdword, :ptr, :ptr
get_aligned_area	proc :ptr, :ptr, :GtkCellRendererState, :ptr, :ptr
snapshot		proc :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
activate		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
start_editing		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
editing_canceled	proc :ptr
editing_started		proc :ptr, :ptr, :ptr
padding			gpointer 8 dup(?)
GtkCellRendererClass	ends

gtk_cell_renderer_get_type proto

gtk_cell_renderer_get_request_mode proto :ptr
gtk_cell_renderer_get_preferred_width proto :ptr, :ptr, :ptr, :ptr
gtk_cell_renderer_get_preferred_height_for_width proto :ptr, :ptr, :sdword, :ptr, :ptr
gtk_cell_renderer_get_preferred_height proto :ptr, :ptr, :ptr, :ptr
gtk_cell_renderer_get_preferred_width_for_height proto :ptr, :ptr, :sdword, :ptr, :ptr
gtk_cell_renderer_get_preferred_size proto :ptr, :ptr, :ptr, :ptr
gtk_cell_renderer_get_aligned_area proto :ptr, :ptr, :GtkCellRendererState, :ptr, :ptr
gtk_cell_renderer_snapshot proto :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
gtk_cell_renderer_activate proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
gtk_cell_renderer_start_editing proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState

gtk_cell_renderer_set_fixed_size proto :ptr, :sdword, :sdword
gtk_cell_renderer_get_fixed_size proto :ptr, :ptr, :ptr

gtk_cell_renderer_set_alignment proto :ptr, :real4, :real4
gtk_cell_renderer_get_alignment proto :ptr, :ptr, :ptr

gtk_cell_renderer_set_padding proto :ptr, :sdword, :sdword
gtk_cell_renderer_get_padding proto :ptr, :ptr, :ptr

gtk_cell_renderer_set_visible proto :ptr, :gboolean
gtk_cell_renderer_get_visible proto :ptr

gtk_cell_renderer_set_sensitive proto :ptr, :gboolean
gtk_cell_renderer_get_sensitive proto :ptr

gtk_cell_renderer_is_activatable proto :ptr

gtk_cell_renderer_set_is_expander proto :ptr, :gboolean
gtk_cell_renderer_get_is_expander proto :ptr

gtk_cell_renderer_set_is_expanded proto :ptr, :gboolean
gtk_cell_renderer_get_is_expanded proto :ptr
gtk_cell_renderer_stop_editing proto :ptr, :gboolean
_gtk_cell_renderer_calc_offset proto :ptr, :ptr, :GtkTextDirection, :sdword, :sdword, :ptr, :ptr
gtk_cell_renderer_get_state proto :ptr, :ptr, :GtkCellRendererState

endif

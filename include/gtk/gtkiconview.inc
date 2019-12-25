ifndef __GTK_ICON_VIEW_H__
__GTK_ICON_VIEW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
include gtk/gtktreemodel.inc
include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtkselection.inc
include gtk/gtktooltip.inc

G_BEGIN_DECLS

GTK_TYPE_ICON_VIEW equ <gtk_icon_view_get_type>
GTK_ICON_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_VIEW, GtkIconView))>
	endm
GTK_ICON_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ICON_VIEW, GtkIconViewClass))>
	endm
GTK_IS_ICON_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_VIEW))>
	endm
GTK_IS_ICON_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ICON_VIEW))>
	endm
GTK_ICON_VIEW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ICON_VIEW, GtkIconViewClass))>
	endm

CALLBACKC(GtkIconViewForeachFunc, :ptr GtkIconView, :ptr GtkTreePath, :gpointer)

.enum GtkIconViewDropPosition {
  GTK_ICON_VIEW_NO_DROP,
  GTK_ICON_VIEW_DROP_INTO,
  GTK_ICON_VIEW_DROP_LEFT,
  GTK_ICON_VIEW_DROP_RIGHT,
  GTK_ICON_VIEW_DROP_ABOVE,
  GTK_ICON_VIEW_DROP_BELOW
}

GtkIconView		STRUC
parent			GtkContainer <>
priv			ptr_t ?
GtkIconView		ENDS

GtkIconViewClass	STRUC
parent_class		GtkContainerClass <>
item_activated		proc :ptr GtkIconView, :ptr GtkTreePath
selection_changed	proc :ptr GtkIconView
select_all		proc :ptr GtkIconView
unselect_all		proc :ptr GtkIconView
select_cursor_item	proc :ptr GtkIconView
toggle_cursor_item	proc :ptr GtkIconView
move_cursor		proc :ptr GtkIconView, :GtkMovementStep, :gint
activate_cursor_item	proc :ptr GtkIconView
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkIconViewClass	ENDS

;GType
gtk_icon_view_get_type proto __cdecl
;GtkWidget
gtk_icon_view_new proto __cdecl
;GtkWidget
gtk_icon_view_new_with_area proto __cdecl \
		  area: ptr GtkCellArea

;GtkWidget
gtk_icon_view_new_with_model proto __cdecl \
		 model: ptr GtkTreeModel


;void
gtk_icon_view_set_model proto __cdecl \
	     icon_view: ptr GtkIconView,
		 model: ptr GtkTreeModel

;GtkTreeModel
gtk_icon_view_get_model proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_text_column proto __cdecl \
	     icon_view: ptr GtkIconView,
		column: gint

;gint
gtk_icon_view_get_text_column proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_markup_column proto __cdecl \
	     icon_view: ptr GtkIconView,
		column: gint

;gint
gtk_icon_view_get_markup_column proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_pixbuf_column proto __cdecl \
	     icon_view: ptr GtkIconView,
		column: gint

;gint
gtk_icon_view_get_pixbuf_column proto __cdecl \
	     icon_view: ptr GtkIconView


;void
gtk_icon_view_set_item_orientation proto __cdecl \
	     icon_view: ptr GtkIconView,
	   orientation: GtkOrientation

;GtkOrientation
gtk_icon_view_get_item_orientation proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_columns proto __cdecl \
	     icon_view: ptr GtkIconView,
	       columns: gint

;gint
gtk_icon_view_get_columns proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_item_width proto __cdecl \
	     icon_view: ptr GtkIconView,
	    item_width: gint

;gint
gtk_icon_view_get_item_width proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_spacing proto __cdecl \
	     icon_view: ptr GtkIconView,
	       spacing: gint

;gint
gtk_icon_view_get_spacing proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_row_spacing proto __cdecl \
	     icon_view: ptr GtkIconView,
	   row_spacing: gint

;gint
gtk_icon_view_get_row_spacing proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_column_spacing proto __cdecl \
	     icon_view: ptr GtkIconView,
	column_spacing: gint

;gint
gtk_icon_view_get_column_spacing proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_margin proto __cdecl \
	     icon_view: ptr GtkIconView,
		margin: gint

;gint
gtk_icon_view_get_margin proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_item_padding proto __cdecl \
	     icon_view: ptr GtkIconView,
	  item_padding: gint

;gint
gtk_icon_view_get_item_padding proto __cdecl \
	     icon_view: ptr GtkIconView


;GtkTreePath
gtk_icon_view_get_path_at_pos proto __cdecl \
	     icon_view: ptr GtkIconView,
		     x: gint,
		     y: gint

;gboolean
gtk_icon_view_get_item_at_pos proto __cdecl \
	     icon_view: ptr GtkIconView,
		     x: gint,
		     y: gint,
		  path: ptr GtkTreePath,
		  cell: ptr GtkCellRenderer

;gboolean
gtk_icon_view_get_visible_range proto __cdecl \
	     icon_view: ptr GtkIconView,
	    start_path: ptr GtkTreePath,
	      end_path: ptr GtkTreePath

;void
gtk_icon_view_set_activate_on_single_click proto __cdecl \
	     icon_view: ptr GtkIconView,
		single: gboolean

;gboolean
gtk_icon_view_get_activate_on_single_click proto __cdecl \
	     icon_view: ptr GtkIconView


;void
gtk_icon_view_selected_foreach proto __cdecl \
	     icon_view: ptr GtkIconView,
		  func: GtkIconViewForeachFunc,
		  data: gpointer

;void
gtk_icon_view_set_selection_mode proto __cdecl \
	     icon_view: ptr GtkIconView,
		  mode: GtkSelectionMode

;GtkSelectionMode
gtk_icon_view_get_selection_mode proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_select_path proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;void
gtk_icon_view_unselect_path proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;gboolean
gtk_icon_view_path_is_selected proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;gint
gtk_icon_view_get_item_row proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;gint
gtk_icon_view_get_item_column proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;GList
gtk_icon_view_get_selected_items proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_select_all proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_unselect_all proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_item_activated proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath

;void
gtk_icon_view_set_cursor proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
		  cell: ptr GtkCellRenderer,
	 start_editing: gboolean

;gboolean
gtk_icon_view_get_cursor proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
		  cell: ptr GtkCellRenderer

;void
gtk_icon_view_scroll_to_path proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
	     use_align: gboolean,
	     row_align: gfloat,
	     col_align: gfloat


;void
gtk_icon_view_enable_model_drag_source proto __cdecl \
	     icon_view: ptr GtkIconView,
     start_button_mask: GdkModifierType,
	       targets: ptr GtkTargetEntry,
	     n_targets: gint,
	       actions: GdkDragAction

;void
gtk_icon_view_enable_model_drag_dest proto __cdecl \
	     icon_view: ptr GtkIconView,
	       targets: ptr GtkTargetEntry,
	     n_targets: gint,
	       actions: GdkDragAction

;void
gtk_icon_view_unset_model_drag_source proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_unset_model_drag_dest proto __cdecl \
	     icon_view: ptr GtkIconView

;void
gtk_icon_view_set_reorderable proto __cdecl \
	     icon_view: ptr GtkIconView,
	   reorderable: gboolean

;gboolean
gtk_icon_view_get_reorderable proto __cdecl \
	     icon_view: ptr GtkIconView



;void
gtk_icon_view_set_drag_dest_item proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
		   pos: GtkIconViewDropPosition

;void
gtk_icon_view_get_drag_dest_item proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
		   pos: ptr GtkIconViewDropPosition

;gboolean
gtk_icon_view_get_dest_item_at_pos proto __cdecl \
	     icon_view: ptr GtkIconView,
		drag_x: gint,
		drag_y: gint,
		  path: ptr GtkTreePath,
		   pos: ptr GtkIconViewDropPosition

;cairo_surface_t
gtk_icon_view_create_drag_icon proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath


;void
gtk_icon_view_convert_widget_to_bin_window_coords proto __cdecl \
	     icon_view: ptr GtkIconView,
		    wx: gint,
		    wy: gint,
		   _bx: ptr gint,
		    by: ptr gint

;gboolean
gtk_icon_view_get_cell_rect proto __cdecl \
	     icon_view: ptr GtkIconView,
		  path: ptr GtkTreePath,
		  cell: ptr GtkCellRenderer,
		  rect: ptr GdkRectangle



;void
gtk_icon_view_set_tooltip_item proto __cdecl \
	     icon_view: ptr GtkIconView,
	       tooltip: ptr GtkTooltip,
		  path: ptr GtkTreePath

;void
gtk_icon_view_set_tooltip_cell proto __cdecl \
	     icon_view: ptr GtkIconView,
	       tooltip: ptr GtkTooltip,
		  path: ptr GtkTreePath,
		  cell: ptr GtkCellRenderer

;gboolean
gtk_icon_view_get_tooltip_context proto __cdecl \
	     icon_view: ptr GtkIconView,
		     x: ptr gint,
		     y: ptr gint,
	  keyboard_tip: gboolean,
		 model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter

;void
gtk_icon_view_set_tooltip_column proto __cdecl \
	     icon_view: ptr GtkIconView,
		column: gint

;gint
gtk_icon_view_get_tooltip_column proto __cdecl \
	     icon_view: ptr GtkIconView

G_END_DECLS

endif

ifndef __GTK_TREE_VIEW_H__
__GTK_TREE_VIEW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
include gtk/gtktreemodel.inc
include gtk/gtktreeviewcolumn.inc
include gtk/gtkdnd.inc
include gtk/gtkentry.inc

G_BEGIN_DECLS

.enum GtkTreeViewDropPosition {
  GTK_TREE_VIEW_DROP_BEFORE,
  GTK_TREE_VIEW_DROP_AFTER,
  GTK_TREE_VIEW_DROP_INTO_OR_BEFORE,
  GTK_TREE_VIEW_DROP_INTO_OR_AFTER
}

GTK_TYPE_TREE_VIEW equ <gtk_tree_view_get_type>
GTK_TREE_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_VIEW, GtkTreeView))>
	endm
GTK_TREE_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_VIEW, GtkTreeViewClass))>
	endm
GTK_IS_TREE_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_VIEW))>
	endm
GTK_IS_TREE_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_VIEW))>
	endm
GTK_TREE_VIEW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_VIEW, GtkTreeViewClass))>
	endm

GtkTreeView		STRUC
parent			GtkContainer <>
priv			ptr_t ?
GtkTreeView		ENDS

GtkTreeViewClass	STRUC
parent_class		GtkContainerClass <>
row_activated		proc :ptr GtkTreeView, :ptr GtkTreePath, :ptr GtkTreeViewColumn
test_expand_row		proc :ptr GtkTreeView, :ptr GtkTreeIter, :ptr GtkTreePath
test_collapse_row	proc :ptr GtkTreeView, :ptr GtkTreeIter, :ptr GtkTreePath
row_expanded		proc :ptr GtkTreeView, :ptr GtkTreeIter, :ptr GtkTreePath
row_collapsed		proc :ptr GtkTreeView, :ptr GtkTreeIter, :ptr GtkTreePath
columns_changed		proc :ptr GtkTreeView
cursor_changed		proc :ptr GtkTreeView
move_cursor		proc :ptr GtkTreeView, :GtkMovementStep, :gint
select_all		proc :ptr GtkTreeView
unselect_all		proc :ptr GtkTreeView
select_cursor_row	proc :ptr GtkTreeView, :gboolean
toggle_cursor_row	proc :ptr GtkTreeView
expand_collapse_cursor_row proc :ptr GtkTreeView, :gboolean, :gboolean, :gboolean
select_cursor_parent	proc :ptr GtkTreeView
start_interactive_search proc :ptr GtkTreeView
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkTreeViewClass	ENDS


CALLBACKC(GtkTreeViewColumnDropFunc, :ptr GtkTreeView, :ptr GtkTreeViewColumn, :ptr GtkTreeViewColumn, :ptr GtkTreeViewColumn, :gpointer)
CALLBACKC(GtkTreeViewMappingFunc, :ptr GtkTreeView, :ptr GtkTreePath, :gpointer)
CALLBACKC(GtkTreeViewSearchEqualFunc, :ptr GtkTreeModel, :gint, :ptr gchar, :ptr GtkTreeIter, :gpointer)
CALLBACKC(GtkTreeViewRowSeparatorFunc, :ptr GtkTreeModel, :ptr GtkTreeIter, :gpointer)
CALLBACKC(GtkTreeViewSearchPositionFunc, :ptr GtkTreeView, :ptr GtkWidget, :gpointer)

;GType
gtk_tree_view_get_type proto __cdecl
;GtkWidget
gtk_tree_view_new proto __cdecl
;GtkWidget
gtk_tree_view_new_with_model proto __cdecl \
		 model: ptr GtkTreeModel


;GtkTreeModel
gtk_tree_view_get_model proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_model proto __cdecl \
	     tree_view: ptr GtkTreeView,
		 model: ptr GtkTreeModel

;GtkTreeSelection
gtk_tree_view_get_selection proto __cdecl \
	     tree_view: ptr GtkTreeView


;GtkAdjustment
gtk_tree_view_get_hadjustment proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_hadjustment proto __cdecl \
	     tree_view: ptr GtkTreeView,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment
gtk_tree_view_get_vadjustment proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_vadjustment proto __cdecl \
	     tree_view: ptr GtkTreeView,
	    adjustment: ptr GtkAdjustment



;gboolean
gtk_tree_view_get_headers_visible proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_headers_visible proto __cdecl \
	     tree_view: ptr GtkTreeView,
       headers_visible: gboolean

;void
gtk_tree_view_columns_autosize proto __cdecl \
	     tree_view: ptr GtkTreeView

;gboolean
gtk_tree_view_get_headers_clickable proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_headers_clickable proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       setting: gboolean

;void
gtk_tree_view_set_rules_hint proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       setting: gboolean

;gboolean
gtk_tree_view_get_rules_hint proto __cdecl \
	     tree_view: ptr GtkTreeView

;gboolean
gtk_tree_view_get_activate_on_single_click proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_activate_on_single_click proto __cdecl \
	     tree_view: ptr GtkTreeView,
		single: gboolean


;gint
gtk_tree_view_append_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: ptr GtkTreeViewColumn

;gint
gtk_tree_view_remove_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: ptr GtkTreeViewColumn

;gint
gtk_tree_view_insert_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: ptr GtkTreeViewColumn,
	      position: gint

;gint
gtk_tree_view_insert_column_with_attributes proto _CDecl \
	     tree_view: ptr GtkTreeView,
	      position: gint,
		 title: ptr gchar,
		  cell: ptr GtkCellRenderer,
		      : vararg
;gint
gtk_tree_view_insert_column_with_data_func proto __cdecl \
	     tree_view: ptr GtkTreeView,
	      position: gint,
		 title: ptr gchar,
		  cell: ptr GtkCellRenderer,
		  func: GtkTreeCellDataFunc,
		  data: gpointer,
	       dnotify: GDestroyNotify


;guint
gtk_tree_view_get_n_columns proto __cdecl \
	     tree_view: ptr GtkTreeView

;GtkTreeViewColumn
gtk_tree_view_get_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		     n: gint

;GList
gtk_tree_view_get_columns proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_move_column_after proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: ptr GtkTreeViewColumn,
	   base_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_set_expander_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: ptr GtkTreeViewColumn

;GtkTreeViewColumn
gtk_tree_view_get_expander_column proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_column_drag_function proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  func: GtkTreeViewColumnDropFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify


;void
gtk_tree_view_scroll_to_point proto __cdecl \
	     tree_view: ptr GtkTreeView,
		tree_x: gint,
		tree_y: gint

;void
gtk_tree_view_scroll_to_cell proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
	     use_align: gboolean,
	     row_align: gfloat,
	     col_align: gfloat

;void
gtk_tree_view_row_activated proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn

;void
gtk_tree_view_expand_all proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_collapse_all proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_expand_to_path proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath

;gboolean
gtk_tree_view_expand_row proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
	      open_all: gboolean

;gboolean
gtk_tree_view_collapse_row proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath

;void
gtk_tree_view_map_expanded_rows proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  func: GtkTreeViewMappingFunc,
		  data: gpointer

;gboolean
gtk_tree_view_row_expanded proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath

;void
gtk_tree_view_set_reorderable proto __cdecl \
	     tree_view: ptr GtkTreeView,
	   reorderable: gboolean

;gboolean
gtk_tree_view_get_reorderable proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_cursor proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
	  focus_column: ptr GtkTreeViewColumn,
	 start_editing: gboolean

;void
gtk_tree_view_set_cursor_on_cell proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
	  focus_column: ptr GtkTreeViewColumn,
	    focus_cell: ptr GtkCellRenderer,
	 start_editing: gboolean

;void
gtk_tree_view_get_cursor proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
	  focus_column: ptr GtkTreeViewColumn



;GdkWindow
gtk_tree_view_get_bin_window proto __cdecl \
	     tree_view: ptr GtkTreeView

;gboolean
gtk_tree_view_get_path_at_pos proto __cdecl \
	     tree_view: ptr GtkTreeView,
		     x: gint,
		     y: gint,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
		cell_x: ptr gint,
		cell_y: ptr gint

;void
gtk_tree_view_get_cell_area proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
		  rect: ptr GdkRectangle

;void
gtk_tree_view_get_background_area proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
		  rect: ptr GdkRectangle

;void
gtk_tree_view_get_visible_rect proto __cdecl \
	     tree_view: ptr GtkTreeView,
	  visible_rect: ptr GdkRectangle

;gboolean
gtk_tree_view_get_visible_range proto __cdecl \
	     tree_view: ptr GtkTreeView,
	    start_path: ptr GtkTreePath,
	      end_path: ptr GtkTreePath

;gboolean
gtk_tree_view_is_blank_at_pos proto __cdecl \
	     tree_view: ptr GtkTreeView,
		     x: gint,
		     y: gint,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
		cell_x: ptr gint,
		cell_y: ptr gint


;void
gtk_tree_view_enable_model_drag_source proto __cdecl \
	     tree_view: ptr GtkTreeView,
     start_button_mask: GdkModifierType,
	       targets: ptr GtkTargetEntry,
	     n_targets: gint,
	       actions: GdkDragAction

;void
gtk_tree_view_enable_model_drag_dest proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       targets: ptr GtkTargetEntry,
	     n_targets: gint,
	       actions: GdkDragAction

;void
gtk_tree_view_unset_rows_drag_source proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_unset_rows_drag_dest proto __cdecl \
	     tree_view: ptr GtkTreeView



;void
gtk_tree_view_set_drag_dest_row proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		   pos: GtkTreeViewDropPosition

;void
gtk_tree_view_get_drag_dest_row proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath,
		   pos: ptr GtkTreeViewDropPosition

;gboolean
gtk_tree_view_get_dest_row_at_pos proto __cdecl \
	     tree_view: ptr GtkTreeView,
		drag_x: gint,
		drag_y: gint,
		  path: ptr GtkTreePath,
		   pos: ptr GtkTreeViewDropPosition

;cairo_surface_t
gtk_tree_view_create_row_drag_icon proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  path: ptr GtkTreePath


;void
gtk_tree_view_set_enable_search proto __cdecl \
	     tree_view: ptr GtkTreeView,
	 enable_search: gboolean

;gboolean
gtk_tree_view_get_enable_search proto __cdecl \
	     tree_view: ptr GtkTreeView

;gint
gtk_tree_view_get_search_column proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_search_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: gint

;GtkTreeViewSearchEqualFunc
gtk_tree_view_get_search_equal_func proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_search_equal_func proto __cdecl \
	     tree_view: ptr GtkTreeView,
     search_equal_func: GtkTreeViewSearchEqualFunc,
      search_user_data: gpointer,
	search_destroy: GDestroyNotify


;GtkEntry
gtk_tree_view_get_search_entry proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_search_entry proto __cdecl \
	     tree_view: ptr GtkTreeView,
		 entry: ptr GtkEntry

;GtkTreeViewSearchPositionFunc
gtk_tree_view_get_search_position_func proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_search_position_func proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  func: GtkTreeViewSearchPositionFunc,
		  data: gpointer,
	       destroy: GDestroyNotify


;void
gtk_tree_view_convert_widget_to_tree_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		    wx: gint,
		    wy: gint,
		    tx: ptr gint,
		    ty: ptr gint

;void
gtk_tree_view_convert_tree_to_widget_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		    tx: gint,
		    ty: gint,
		    wx: ptr gint,
		    wy: ptr gint

;void
gtk_tree_view_convert_widget_to_bin_window_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		    wx: gint,
		    wy: gint,
		   _bx: ptr gint,
		    by: ptr gint

;void
gtk_tree_view_convert_bin_window_to_widget_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		   _bx: gint,
		    by: gint,
		    wx: ptr gint,
		    wy: ptr gint

;void
gtk_tree_view_convert_tree_to_bin_window_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		    tx: gint,
		    ty: gint,
		   _bx: ptr gint,
		    by: ptr gint

;void
gtk_tree_view_convert_bin_window_to_tree_coords proto __cdecl \
	     tree_view: ptr GtkTreeView,
		   _bx: gint,
		    by: gint,
		    tx: ptr gint,
		    ty: ptr gint


CALLBACKC(GtkTreeDestroyCountFunc, :ptr GtkTreeView, :ptr GtkTreePath, :gint, :gpointer)

;void
gtk_tree_view_set_destroy_count_func proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  func: GtkTreeDestroyCountFunc,
		  data: gpointer,
	       destroy: GDestroyNotify


;void
gtk_tree_view_set_fixed_height_mode proto __cdecl \
	     tree_view: ptr GtkTreeView,
		enable: gboolean

;gboolean
gtk_tree_view_get_fixed_height_mode proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_hover_selection proto __cdecl \
	     tree_view: ptr GtkTreeView,
		 hover: gboolean

;gboolean
gtk_tree_view_get_hover_selection proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_hover_expand proto __cdecl \
	     tree_view: ptr GtkTreeView,
		expand: gboolean

;gboolean
gtk_tree_view_get_hover_expand proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_rubber_banding proto __cdecl \
	     tree_view: ptr GtkTreeView,
		enable: gboolean

;gboolean
gtk_tree_view_get_rubber_banding proto __cdecl \
	     tree_view: ptr GtkTreeView


;gboolean
gtk_tree_view_is_rubber_banding_active proto __cdecl \
	     tree_view: ptr GtkTreeView


;GtkTreeViewRowSeparatorFunc
gtk_tree_view_get_row_separator_func proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_row_separator_func proto __cdecl \
	     tree_view: ptr GtkTreeView,
		  func: GtkTreeViewRowSeparatorFunc,
		  data: gpointer,
	       destroy: GDestroyNotify


;GtkTreeViewGridLines
gtk_tree_view_get_grid_lines proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_grid_lines proto __cdecl \
	     tree_view: ptr GtkTreeView,
	    grid_lines: GtkTreeViewGridLines

;gboolean
gtk_tree_view_get_enable_tree_lines proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_enable_tree_lines proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       enabled: gboolean

;void
gtk_tree_view_set_show_expanders proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       enabled: gboolean

;gboolean
gtk_tree_view_get_show_expanders proto __cdecl \
	     tree_view: ptr GtkTreeView

;void
gtk_tree_view_set_level_indentation proto __cdecl \
	     tree_view: ptr GtkTreeView,
	   indentation: gint

;gint
gtk_tree_view_get_level_indentation proto __cdecl \
	     tree_view: ptr GtkTreeView


;void
gtk_tree_view_set_tooltip_row proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       tooltip: ptr GtkTooltip,
		  path: ptr GtkTreePath

;void
gtk_tree_view_set_tooltip_cell proto __cdecl \
	     tree_view: ptr GtkTreeView,
	       tooltip: ptr GtkTooltip,
		  path: ptr GtkTreePath,
		column: ptr GtkTreeViewColumn,
		  cell: ptr GtkCellRenderer

;gboolean
gtk_tree_view_get_tooltip_context proto __cdecl \
	     tree_view: ptr GtkTreeView,
		     x: ptr gint,
		     y: ptr gint,
	  keyboard_tip: gboolean,
		 model: ptr GtkTreeModel,
		  path: ptr GtkTreePath,
		  iter: ptr GtkTreeIter

;void
gtk_tree_view_set_tooltip_column proto __cdecl \
	     tree_view: ptr GtkTreeView,
		column: gint

;gint
gtk_tree_view_get_tooltip_column proto __cdecl \
	     tree_view: ptr GtkTreeView

G_END_DECLS

endif

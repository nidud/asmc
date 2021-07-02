ifndef __GTK_TREE_VIEW_COLUMN_H__
__GTK_TREE_VIEW_COLUMN_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc
include gtk/gtkcellarea.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_VIEW_COLUMN equ <gtk_tree_view_column_get_type>
GTK_TREE_VIEW_COLUMN macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_VIEW_COLUMN, GtkTreeViewColumn))>
	endm
GTK_TREE_VIEW_COLUMN_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_VIEW_COLUMN, GtkTreeViewColumnClass))>
	endm
GTK_IS_TREE_VIEW_COLUMN macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_VIEW_COLUMN))>
	endm
GTK_IS_TREE_VIEW_COLUMN_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_VIEW_COLUMN))>
	endm
GTK_TREE_VIEW_COLUMN_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_VIEW_COLUMN, GtkTreeViewColumnClass))>
	endm

.enum GtkTreeViewColumnSizing {
  GTK_TREE_VIEW_COLUMN_GROW_ONLY,
  GTK_TREE_VIEW_COLUMN_AUTOSIZE,
  GTK_TREE_VIEW_COLUMN_FIXED
}

CALLBACKC(GtkTreeCellDataFunc, :ptr GtkTreeViewColumn, :ptr GtkCellRenderer, :ptr GtkTreeModel, :ptr GtkTreeIter, :gpointer)

GtkTreeViewColumn	STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr_t ?
GtkTreeViewColumn	ENDS

GtkTreeViewColumnClass	STRUC
parent_class		GInitiallyUnownedClass <>
clicked			proc :ptr GtkTreeViewColumn
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTreeViewColumnClass	ENDS

;GType
gtk_tree_view_column_get_type proto __cdecl
;GtkTreeViewColumn
gtk_tree_view_column_new proto __cdecl
;GtkTreeViewColumn
gtk_tree_view_column_new_with_area proto __cdecl \
		  area: ptr GtkCellArea

;GtkTreeViewColumn
gtk_tree_view_column_new_with_attributes proto _CDecl \
		 title: ptr gchar,
		  cell: ptr GtkCellRenderer,
		      : vararg

;void
gtk_tree_view_column_pack_start proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		  cell: ptr GtkCellRenderer,
		expand: gboolean

;void
gtk_tree_view_column_pack_end proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		  cell: ptr GtkCellRenderer,
		expand: gboolean

;void
gtk_tree_view_column_clear proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_add_attribute proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	 cell_renderer: ptr GtkCellRenderer,
	     attribute: ptr gchar,
		column: gint

;void
gtk_tree_view_column_set_attributes proto _CDecl \
	   tree_column: ptr GtkTreeViewColumn,
	 cell_renderer: ptr GtkCellRenderer,
		      : vararg

;void
gtk_tree_view_column_set_cell_data_func proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	 cell_renderer: ptr GtkCellRenderer,
		  func: GtkTreeCellDataFunc,
	     func_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_tree_view_column_clear_attributes proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	 cell_renderer: ptr GtkCellRenderer

;void
gtk_tree_view_column_set_spacing proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	       spacing: gint

;gint
gtk_tree_view_column_get_spacing proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_visible proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	       visible: gboolean

;gboolean
gtk_tree_view_column_get_visible proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_resizable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	     resizable: gboolean

;gboolean
gtk_tree_view_column_get_resizable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_sizing proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		  type: GtkTreeViewColumnSizing

;GtkTreeViewColumnSizing
gtk_tree_view_column_get_sizing proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;gint
gtk_tree_view_column_get_x_offset proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;gint
gtk_tree_view_column_get_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;gint
gtk_tree_view_column_get_fixed_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_fixed_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	   fixed_width: gint

;void
gtk_tree_view_column_set_min_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	     min_width: gint

;gint
gtk_tree_view_column_get_min_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_max_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	     max_width: gint

;gint
gtk_tree_view_column_get_max_width proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_clicked proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn




;void
gtk_tree_view_column_set_title proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		 title: ptr gchar

;const
gtk_tree_view_column_get_title proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_expand proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		expand: gboolean

;gboolean
gtk_tree_view_column_get_expand proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_clickable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	     clickable: gboolean

;gboolean
gtk_tree_view_column_get_clickable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_widget proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		widget: ptr GtkWidget

;GtkWidget
gtk_tree_view_column_get_widget proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_alignment proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		xalign: gfloat

;gfloat
gtk_tree_view_column_get_alignment proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_reorderable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	   reorderable: gboolean

;gboolean
gtk_tree_view_column_get_reorderable proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn




;void
gtk_tree_view_column_set_sort_column_id proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	sort_column_id: gint

;gint
gtk_tree_view_column_get_sort_column_id proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_sort_indicator proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	       setting: gboolean

;gboolean
gtk_tree_view_column_get_sort_indicator proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_set_sort_order proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		 order: GtkSortType

;GtkSortType
gtk_tree_view_column_get_sort_order proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn



;void
gtk_tree_view_column_cell_set_cell_data proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
	   is_expander: gboolean,
	   is_expanded: gboolean

;void
gtk_tree_view_column_cell_get_size proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	     cell_area: ptr GdkRectangle,
	      x_offset: ptr gint,
	      y_offset: ptr gint,
		 width: ptr gint,
		height: ptr gint

;gboolean
gtk_tree_view_column_cell_is_visible proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;void
gtk_tree_view_column_focus_cell proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
		  cell: ptr GtkCellRenderer

;gboolean
gtk_tree_view_column_cell_get_position proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn,
	 cell_renderer: ptr GtkCellRenderer,
	      x_offset: ptr gint,
		 width: ptr gint

;void
gtk_tree_view_column_queue_resize proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;GtkWidget
gtk_tree_view_column_get_tree_view proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn

;GtkWidget
gtk_tree_view_column_get_button proto __cdecl \
	   tree_column: ptr GtkTreeViewColumn


G_END_DECLS


endif

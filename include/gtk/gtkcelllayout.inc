ifndef __GTK_CELL_LAYOUT_H__
__GTK_CELL_LAYOUT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtkbuildable.inc
include gtk/gtkbuilder.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_LAYOUT equ <gtk_cell_layout_get_type>
GTK_CELL_LAYOUT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_LAYOUT, GtkCellLayout))>
	endm
GTK_IS_CELL_LAYOUT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_LAYOUT))>
	endm
GTK_CELL_LAYOUT_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_CELL_LAYOUT, GtkCellLayoutIface))>
	endm

CALLBACKC(GtkCellLayoutDataFunc, :ptr GtkCellLayout, :ptr GtkCellRenderer, :ptr GtkTreeModel, :ptr GtkTreeIter, :gpointer)

GtkCellLayoutIface	STRUC
g_iface			GTypeInterface <>
pack_start		proc :ptr GtkCellLayout, :ptr GtkCellRenderer, :gboolean
pack_end		proc :ptr GtkCellLayout, :ptr GtkCellRenderer, :gboolean
clear			proc :ptr GtkCellLayout
add_attribute		proc :ptr GtkCellLayout, :ptr GtkCellRenderer, :ptr gchar, :gint
set_cell_data_func	proc :ptr GtkCellLayout, :ptr GtkCellRenderer, :GtkCellLayoutDataFunc, :gpointer, :GDestroyNotify
clear_attributes	proc :ptr GtkCellLayout, :ptr GtkCellRenderer
reorder			proc :ptr GtkCellLayout, :ptr GtkCellRenderer, :gint
get_cells		proc :ptr GtkCellLayout
get_area		proc :ptr GtkCellLayout
GtkCellLayoutIface	ENDS

;GType
gtk_cell_layout_get_type proto __cdecl
;void
gtk_cell_layout_pack_start proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
		expand: gboolean

;void
gtk_cell_layout_pack_end proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
		expand: gboolean

;GList
gtk_cell_layout_get_cells proto __cdecl \
	   cell_layout: ptr GtkCellLayout

;void
gtk_cell_layout_clear proto __cdecl \
	   cell_layout: ptr GtkCellLayout

;void
gtk_cell_layout_set_attributes proto _CDecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
		      : vararg

;void
gtk_cell_layout_add_attribute proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
	     attribute: ptr gchar,
		column: gint

;void
gtk_cell_layout_set_cell_data_func proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
		  func: GtkCellLayoutDataFunc,
	     func_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_cell_layout_clear_attributes proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer

;void
gtk_cell_layout_reorder proto __cdecl \
	   cell_layout: ptr GtkCellLayout,
		  cell: ptr GtkCellRenderer,
	      position: gint

;GtkCellArea
gtk_cell_layout_get_area proto __cdecl \
	   cell_layout: ptr GtkCellLayout


_gtk_cell_layout_buildable_custom_tag_start proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
	       tagname: ptr gchar,
		parser: ptr GMarkupParser,
		  data: ptr gpointer

_gtk_cell_layout_buildable_custom_tag_end proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
	       tagname: ptr gchar,
		  data: ptr gpointer

;void
_gtk_cell_layout_buildable_add_child proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
		  type: ptr gchar


G_END_DECLS

endif

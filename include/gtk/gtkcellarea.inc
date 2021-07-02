ifndef __GTK_CELL_AREA_H__
__GTK_CELL_AREA_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtkwidget.inc
include gtk/gtktreemodel.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_AREA equ <gtk_cell_area_get_type>
GTK_CELL_AREA macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA, GtkCellArea))>
	endm
GTK_CELL_AREA_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_AREA, GtkCellAreaClass))>
	endm
GTK_IS_CELL_AREA macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA))>
	endm
GTK_IS_CELL_AREA_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_AREA))>
	endm
GTK_CELL_AREA_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_AREA, GtkCellAreaClass))>
	endm

GTK_CELL_AREA_WARN_INVALID_CELL_PROPERTY_ID macro object, property_id, pspec
	exitm<.err>
	endm

CALLBACKC(GtkCellCallback, :ptr GtkCellRenderer, :ptr gpointer)
CALLBACKC(GtkCellAllocCallback, :ptr GtkCellRenderer, :ptr GdkRectangle, :ptr GdkRectangle, :gpointer)


GtkCellArea		STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr_t ?
GtkCellArea		ENDS

GtkCellAreaClass	STRUC
parent_class		GInitiallyUnownedClass <>
_add			proc :ptr GtkCellArea, :ptr GtkCellRenderer
remove			proc :ptr GtkCellArea, :ptr GtkCellRenderer
foreach			proc :ptr GtkCellArea, :GtkCellCallback, :gpointer
foreach_alloc		proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr GdkRectangle, :ptr GdkRectangle, :GtkCellAllocCallback, :gpointer
event			proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr GdkEvent, :ptr GdkRectangle, :GtkCellRendererState
render			proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr cairo_t, :ptr GdkRectangle, :ptr GdkRectangle, :GtkCellRendererState, :gboolean
apply_attributes	proc :ptr GtkCellArea, :ptr GtkTreeModel, :ptr GtkTreeIter, :gboolean, :gboolean
create_context		proc :ptr GtkCellArea
copy_context		proc :ptr GtkCellArea, :ptr GtkCellAreaContext
get_request_mode	proc :ptr GtkCellArea
get_preferred_width	proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_height_for_width proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :gint, :ptr gint, :ptr gint
get_preferred_height	proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_width_for_height proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :gint, :ptr gint, :ptr gint
set_cell_property	proc :ptr GtkCellArea, :ptr GtkCellRenderer, :guint, :ptr GValue, :ptr GParamSpec
get_cell_property	proc :ptr GtkCellArea, :ptr GtkCellRenderer, :guint, :ptr GValue, :ptr GParamSpec
focus			proc :ptr GtkCellArea, :GtkDirectionType
is_activatable		proc :ptr GtkCellArea
activate		proc :ptr GtkCellArea, :ptr GtkCellAreaContext, :ptr GtkWidget, :ptr GdkRectangle, :GtkCellRendererState, :gboolean
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkCellAreaClass	ENDS

;GType
gtk_cell_area_get_type proto __cdecl

;void
gtk_cell_area_add proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer

;void
gtk_cell_area_remove proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer

;gboolean
gtk_cell_area_has_renderer proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer

;void
gtk_cell_area_foreach proto __cdecl \
		  area: ptr GtkCellArea,
	      callback: GtkCellCallback,
	 callback_data: gpointer

;void
gtk_cell_area_foreach_alloc proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	     cell_area: ptr GdkRectangle,
       background_area: ptr GdkRectangle,
	      callback: GtkCellAllocCallback,
	 callback_data: gpointer

;gint
gtk_cell_area_event proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
		 event: ptr GdkEvent,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState

;void
gtk_cell_area_render proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
		    cr: ptr cairo_t,
       background_area: ptr GdkRectangle,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState,
	   paint_focus: gboolean


;void
gtk_cell_area_get_cell_allocation proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	      renderer: ptr GtkCellRenderer,
	     cell_area: ptr GdkRectangle,
	    allocation: ptr GdkRectangle

;GtkCellRenderer
gtk_cell_area_get_cell_at_position proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	     cell_area: ptr GdkRectangle,
		     x: gint,
		     y: gint,
	    alloc_area: ptr GdkRectangle


;GtkCellAreaContext
gtk_cell_area_create_context proto __cdecl \
		  area: ptr GtkCellArea

;GtkCellAreaContext
gtk_cell_area_copy_context proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext

;GtkSizeRequestMode
gtk_cell_area_get_request_mode proto __cdecl \
		  area: ptr GtkCellArea

;void
gtk_cell_area_get_preferred_width proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_cell_area_get_preferred_height_for_width proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
		 width: gint,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_cell_area_get_preferred_height proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_cell_area_get_preferred_width_for_height proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
		height: gint,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;const
gtk_cell_area_get_current_path_string proto __cdecl \
		  area: ptr GtkCellArea



;void
gtk_cell_area_apply_attributes proto __cdecl \
		  area: ptr GtkCellArea,
	    tree_model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter,
	   is_expander: gboolean,
	   is_expanded: gboolean

;void
gtk_cell_area_attribute_connect proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	     attribute: ptr gchar,
		column: gint

;void
gtk_cell_area_attribute_disconnect proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	     attribute: ptr gchar

;gint
gtk_cell_area_attribute_get_column proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	     attribute: ptr gchar



;void
gtk_cell_area_class_install_cell_property proto __cdecl \
		aclass: ptr GtkCellAreaClass,
	   property_id: guint,
		 pspec: ptr GParamSpec

;GParamSpec*
gtk_cell_area_class_find_cell_property proto __cdecl \
		aclass: ptr GtkCellAreaClass,
	 property_name: ptr gchar

;GParamSpec**
gtk_cell_area_class_list_cell_properties proto __cdecl \
		aclass: ptr GtkCellAreaClass,
	  n_properties: ptr guint

;void
gtk_cell_area_add_with_properties proto _CDecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_cell_area_cell_set proto _CDecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_cell_area_cell_get proto _CDecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
       first_prop_name: ptr gchar,
		      : vararg

;void
gtk_cell_area_cell_set_valist proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
   first_property_name: ptr gchar,
	      var_args: va_list

;void
gtk_cell_area_cell_get_valist proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
   first_property_name: ptr gchar,
	      var_args: va_list

;void
gtk_cell_area_cell_set_property proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	 property_name: ptr gchar,
		 value: ptr GValue

;void
gtk_cell_area_cell_get_property proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	 property_name: ptr gchar,
		 value: ptr GValue


;gboolean
gtk_cell_area_is_activatable proto __cdecl \
		  area: ptr GtkCellArea

;gboolean
gtk_cell_area_activate proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext,
		widget: ptr GtkWidget,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState,
	     edit_only: gboolean

;gboolean
gtk_cell_area_focus proto __cdecl \
		  area: ptr GtkCellArea,
	     direction: GtkDirectionType

;void
gtk_cell_area_set_focus_cell proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer

;GtkCellRenderer
gtk_cell_area_get_focus_cell proto __cdecl \
		  area: ptr GtkCellArea



;void
gtk_cell_area_add_focus_sibling proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	       sibling: ptr GtkCellRenderer

;void
gtk_cell_area_remove_focus_sibling proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	       sibling: ptr GtkCellRenderer

;gboolean
gtk_cell_area_is_focus_sibling proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	       sibling: ptr GtkCellRenderer

;const
gtk_cell_area_get_focus_siblings proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer

;GtkCellRenderer
gtk_cell_area_get_focus_from_sibling proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer


;GtkCellRenderer
gtk_cell_area_get_edited_cell proto __cdecl \
		  area: ptr GtkCellArea

;GtkCellEditable
gtk_cell_area_get_edit_widget proto __cdecl \
		  area: ptr GtkCellArea

;gboolean
gtk_cell_area_activate_cell proto __cdecl \
		  area: ptr GtkCellArea,
		widget: ptr GtkWidget,
	      renderer: ptr GtkCellRenderer,
		 event: ptr GdkEvent,
	     cell_area: ptr GdkRectangle,
		 flags: GtkCellRendererState

;void
gtk_cell_area_stop_editing proto __cdecl \
		  area: ptr GtkCellArea,
	      canceled: gboolean



;void
gtk_cell_area_inner_cell_area proto __cdecl \
		  area: ptr GtkCellArea,
		widget: ptr GtkWidget,
	     cell_area: ptr GdkRectangle,
	    inner_area: ptr GdkRectangle


;void
gtk_cell_area_request_renderer proto __cdecl \
		  area: ptr GtkCellArea,
	      renderer: ptr GtkCellRenderer,
	   orientation: GtkOrientation,
		widget: ptr GtkWidget,
	      for_size: gint,
	  minimum_size: ptr gint,
	  natural_size: ptr gint


;void
_gtk_cell_area_set_cell_data_func_with_proxy proto __cdecl \
		  area: ptr GtkCellArea,
		  cell: ptr GtkCellRenderer,
		  func: GFunc,
	     func_data: gpointer,
	       destroy: GDestroyNotify,
		 proxy: gpointer


G_END_DECLS

endif

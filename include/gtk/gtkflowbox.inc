ifndef __GTK_FLOW_BOX_H__
__GTK_FLOW_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_FLOW_BOX equ <gtk_flow_box_get_type>
GTK_FLOW_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FLOW_BOX, GtkFlowBox))>
	endm
GTK_FLOW_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FLOW_BOX, GtkFlowBoxClass))>
	endm
GTK_IS_FLOW_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FLOW_BOX))>
	endm
GTK_IS_FLOW_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FLOW_BOX))>
	endm
GTK_FLOW_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FLOW_BOX, GtkFlowBoxClass))>
	endm

GtkFlowBox		STRUC
container		GtkContainer <>
GtkFlowBox		ENDS

GtkFlowBoxClass		STRUC
parent_class		GtkContainerClass <>
child_activated		proc :ptr GtkFlowBox, :ptr GtkFlowBoxChild
selected_children_changed proc :ptr GtkFlowBox
activate_cursor_child	proc :ptr GtkFlowBox
toggle_cursor_child	proc :ptr GtkFlowBox
move_cursor		proc :ptr GtkFlowBox, :GtkMovementStep, :gint
select_all		proc :ptr GtkFlowBox
unselect_all		proc :ptr GtkFlowBox
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
GtkFlowBoxClass		ENDS

GTK_TYPE_FLOW_BOX_CHILD equ <gtk_flow_box_child_get_type>
GTK_FLOW_BOX_CHILD macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FLOW_BOX_CHILD, GtkFlowBoxChild))>
	endm
GTK_FLOW_BOX_CHILD_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FLOW_BOX_CHILD, GtkFlowBoxChildClass))>
	endm
GTK_IS_FLOW_BOX_CHILD macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FLOW_BOX_CHILD))>
	endm
GTK_IS_FLOW_BOX_CHILD_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FLOW_BOX_CHILD))>
	endm
GTK_FLOW_BOX_CHILD_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), EG_TYPE_FLOW_BOX_CHILD, GtkFlowBoxChildClass))>
	endm

GtkFlowBoxChild		STRUC
parent_instance		GtkBin <>
GtkFlowBoxChild		ENDS

GtkFlowBoxChildClass	STRUC
parent_class		GtkBinClass <>
 activate		proc :ptr GtkFlowBoxChild
_gtk_reserved1		proc
_gtk_reserved2		proc
GtkFlowBoxChildClass	ENDS

CALLBACKC(GtkFlowBoxCreateWidgetFunc, :gpointer, :gpointer)

;GType
gtk_flow_box_child_get_type proto __cdecl
;GtkWidget*
gtk_flow_box_child_new proto __cdecl
;gint
gtk_flow_box_child_get_index proto __cdecl \
		 child: ptr GtkFlowBoxChild

;gboolean
gtk_flow_box_child_is_selected proto __cdecl \
		 child: ptr GtkFlowBoxChild

;void
gtk_flow_box_child_changed proto __cdecl \
		 child: ptr GtkFlowBoxChild



;GType
gtk_flow_box_get_type proto __cdecl

;GtkWidget
gtk_flow_box_new proto __cdecl

;void
gtk_flow_box_bind_model proto __cdecl \
		   box: ptr GtkFlowBox,
		 model: ptr GListModel,
    create_widget_func: GtkFlowBoxCreateWidgetFunc,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify


;void
gtk_flow_box_set_homogeneous proto __cdecl \
		   box: ptr GtkFlowBox,
	   homogeneous: gboolean

;gboolean
gtk_flow_box_get_homogeneous proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_set_row_spacing proto __cdecl \
		   box: ptr GtkFlowBox,
	       spacing: guint

;guint
gtk_flow_box_get_row_spacing proto __cdecl \
		   box: ptr GtkFlowBox


;void
gtk_flow_box_set_column_spacing proto __cdecl \
		   box: ptr GtkFlowBox,
	       spacing: guint

;guint
gtk_flow_box_get_column_spacing proto __cdecl \
		   box: ptr GtkFlowBox


;void
gtk_flow_box_set_min_children_per_line proto __cdecl \
		   box: ptr GtkFlowBox,
	    n_children: guint

;guint
gtk_flow_box_get_min_children_per_line proto __cdecl \
		   box: ptr GtkFlowBox


;void
gtk_flow_box_set_max_children_per_line proto __cdecl \
		   box: ptr GtkFlowBox,
	    n_children: guint

;guint
gtk_flow_box_get_max_children_per_line proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_set_activate_on_single_click proto __cdecl \
		   box: ptr GtkFlowBox,
		single: gboolean

;gboolean
gtk_flow_box_get_activate_on_single_click proto __cdecl \
		   box: ptr GtkFlowBox


;void
gtk_flow_box_insert proto __cdecl \
		   box: ptr GtkFlowBox,
		widget: ptr GtkWidget,
	      position: gint

;GtkFlowBoxChild
gtk_flow_box_get_child_at_index proto __cdecl \
		   box: ptr GtkFlowBox,
		   idx: gint


CALLBACKC(GtkFlowBoxForeachFunc, :ptr GtkFlowBox, :ptr GtkFlowBoxChild, :gpointer)

;void
gtk_flow_box_selected_foreach proto __cdecl \
		   box: ptr GtkFlowBox,
		  func: GtkFlowBoxForeachFunc,
		  data: gpointer

;GList
gtk_flow_box_get_selected_children proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_select_child proto __cdecl \
		   box: ptr GtkFlowBox,
		 child: ptr GtkFlowBoxChild

;void
gtk_flow_box_unselect_child proto __cdecl \
		   box: ptr GtkFlowBox,
		 child: ptr GtkFlowBoxChild

;void
gtk_flow_box_select_all proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_unselect_all proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_set_selection_mode proto __cdecl \
		   box: ptr GtkFlowBox,
		  mode: GtkSelectionMode

;GtkSelectionMode
gtk_flow_box_get_selection_mode proto __cdecl \
		   box: ptr GtkFlowBox

;void
gtk_flow_box_set_hadjustment proto __cdecl \
		   box: ptr GtkFlowBox,
	    adjustment: ptr GtkAdjustment

;void
gtk_flow_box_set_vadjustment proto __cdecl \
		   box: ptr GtkFlowBox,
	    adjustment: ptr GtkAdjustment


CALLBACKC(GtkFlowBoxFilterFunc, :ptr GtkFlowBoxChild, :gpointer)

;void
gtk_flow_box_set_filter_func proto __cdecl \
		   box: ptr GtkFlowBox,
	   filter_func: GtkFlowBoxFilterFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_flow_box_invalidate_filter proto __cdecl \
		   box: ptr GtkFlowBox


CALLBACKC(GtkFlowBoxSortFunc, :ptr GtkFlowBoxChild, :ptr GtkFlowBoxChild, :gpointer)

;void
gtk_flow_box_set_sort_func proto __cdecl \
		   box: ptr GtkFlowBox,
	     sort_func: GtkFlowBoxSortFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_flow_box_invalidate_sort proto __cdecl \
		   box: ptr GtkFlowBox

G_END_DECLS

endif

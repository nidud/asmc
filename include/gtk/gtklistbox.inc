ifndef __GTK_LIST_BOX_H__
__GTK_LIST_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_LIST_BOX equ <gtk_list_box_get_type>
GTK_LIST_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LIST_BOX, GtkListBox))>
	endm
GTK_LIST_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LIST_BOX, GtkListBoxClass))>
	endm
GTK_IS_LIST_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LIST_BOX))>
	endm
GTK_IS_LIST_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LIST_BOX))>
	endm
GTK_LIST_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LIST_BOX, GtkListBoxClass))>
	endm

GtkListBox		STRUC
parent_instance		GtkContainer <>
GtkListBox		ENDS

GtkListBoxClass		STRUC
parent_class		GtkContainerClass <>
row_selected		proc :ptr GtkListBox, :ptr GtkListBoxRow
row_activated		proc :ptr GtkListBox, :ptr GtkListBoxRow
activate_cursor_row	proc :ptr GtkListBox
toggle_cursor_row	proc :ptr GtkListBox
move_cursor		proc :ptr GtkListBox, :GtkMovementStep, :gint
selected_rows_changed	proc :ptr GtkListBox
select_all		proc :ptr GtkListBox
unselect_all		proc :ptr GtkListBox
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
GtkListBoxClass		ENDS

GTK_TYPE_LIST_BOX_ROW	equ <gtk_list_box_row_get_type>
GTK_LIST_BOX_ROW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LIST_BOX_ROW, GtkListBoxRow))>
	endm
GTK_LIST_BOX_ROW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LIST_BOX_ROW, GtkListBoxRowClass))>
	endm
GTK_IS_LIST_BOX_ROW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LIST_BOX_ROW))>
	endm
GTK_IS_LIST_BOX_ROW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LIST_BOX_ROW))>
	endm
GTK_LIST_BOX_ROW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LIST_BOX_ROW, GtkListBoxRowClass))>
	endm

GtkListBoxRow		STRUC
parent_instance		GtkBin <>
GtkListBoxRow		ENDS

GtkListBoxRowClass	STRUC
parent_class		GtkBinClass <>
activate		proc :ptr GtkListBoxRow
_gtk_reserved1		proc
_gtk_reserved2		proc
GtkListBoxRowClass	ENDS

CALLBACKC(GtkListBoxFilterFunc, :ptr GtkListBoxRow, :gpointer)
CALLBACKC(GtkListBoxSortFunc, :ptr GtkListBoxRow, :ptr GtkListBoxRow, :gpointer)
CALLBACKC(GtkListBoxUpdateHeaderFunc, :ptr GtkListBoxRow, :ptr GtkListBoxRow, :gpointer)
CALLBACKC(GtkListBoxCreateWidgetFunc, :gpointer, :gpointer)

;GType
gtk_list_box_row_get_type proto __cdecl
;GtkWidget*
gtk_list_box_row_new proto __cdecl
;GtkWidget*
gtk_list_box_row_get_header proto __cdecl \
		   row: ptr GtkListBoxRow

;void
gtk_list_box_row_set_header proto __cdecl \
		   row: ptr GtkListBoxRow,
		header: ptr GtkWidget

;gint
gtk_list_box_row_get_index proto __cdecl \
		   row: ptr GtkListBoxRow

;void
gtk_list_box_row_changed proto __cdecl \
		   row: ptr GtkListBoxRow


;gboolean
gtk_list_box_row_is_selected proto __cdecl \
		   row: ptr GtkListBoxRow


;void
gtk_list_box_row_set_selectable proto __cdecl \
		   row: ptr GtkListBoxRow,
	    selectable: gboolean

;gboolean
gtk_list_box_row_get_selectable proto __cdecl \
		   row: ptr GtkListBoxRow



;void
gtk_list_box_row_set_activatable proto __cdecl \
		   row: ptr GtkListBoxRow,
	   activatable: gboolean

;gboolean
gtk_list_box_row_get_activatable proto __cdecl \
		   row: ptr GtkListBoxRow


;GType
gtk_list_box_get_type proto __cdecl
;void
gtk_list_box_prepend proto __cdecl \
		   box: ptr GtkListBox,
		 child: ptr GtkWidget

;void
gtk_list_box_insert proto __cdecl \
		   box: ptr GtkListBox,
		 child: ptr GtkWidget,
	      position: gint

;GtkListBoxRow*
gtk_list_box_get_selected_row proto __cdecl \
		   box: ptr GtkListBox

;GtkListBoxRow*
gtk_list_box_get_row_at_index proto __cdecl \
		   box: ptr GtkListBox,
		index_: gint

;GtkListBoxRow*
gtk_list_box_get_row_at_y proto __cdecl \
		   box: ptr GtkListBox,
		     y: gint

;void
gtk_list_box_select_row proto __cdecl \
		   box: ptr GtkListBox,
		   row: ptr GtkListBoxRow

;void
gtk_list_box_set_placeholder proto __cdecl \
		   box: ptr GtkListBox,
	   placeholder: ptr GtkWidget

;void
gtk_list_box_set_adjustment proto __cdecl \
		   box: ptr GtkListBox,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment
gtk_list_box_get_adjustment proto __cdecl \
		   box: ptr GtkListBox


CALLBACKC(GtkListBoxForeachFunc, :ptr GtkListBox, :ptr GtkListBoxRow, :gpointer)

;void
gtk_list_box_selected_foreach proto __cdecl \
		   box: ptr GtkListBox,
		  func: GtkListBoxForeachFunc,
		  data: gpointer

;GList
gtk_list_box_get_selected_rows proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_unselect_row proto __cdecl \
		   box: ptr GtkListBox,
		   row: ptr GtkListBoxRow

;void
gtk_list_box_select_all proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_unselect_all proto __cdecl \
		   box: ptr GtkListBox


;void
gtk_list_box_set_selection_mode proto __cdecl \
		   box: ptr GtkListBox,
		  mode: GtkSelectionMode

;GtkSelectionMode
gtk_list_box_get_selection_mode proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_set_filter_func proto __cdecl \
		   box: ptr GtkListBox,
	   filter_func: GtkListBoxFilterFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_list_box_set_header_func proto __cdecl \
		   box: ptr GtkListBox,
	 update_header: GtkListBoxUpdateHeaderFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_list_box_invalidate_filter proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_invalidate_sort proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_invalidate_headers proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_set_sort_func proto __cdecl \
		   box: ptr GtkListBox,
	     sort_func: GtkListBoxSortFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_list_box_set_activate_on_single_click proto __cdecl \
		   box: ptr GtkListBox,
		single: gboolean

;gboolean
gtk_list_box_get_activate_on_single_click proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_drag_unhighlight_row proto __cdecl \
		   box: ptr GtkListBox

;void
gtk_list_box_drag_highlight_row proto __cdecl \
		   box: ptr GtkListBox,
		   row: ptr GtkListBoxRow

;GtkWidget*
gtk_list_box_new proto __cdecl


;void
gtk_list_box_bind_model proto __cdecl \
		   box: ptr GtkListBox,
		 model: ptr GListModel,
    create_widget_func: GtkListBoxCreateWidgetFunc,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify


G_END_DECLS

endif

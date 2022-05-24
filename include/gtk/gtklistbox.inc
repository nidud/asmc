ifndef __GTK_LIST_BOX_H__
define __GTK_LIST_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_LIST_BOX <gtk_list_box_get_type ()>
GTK_LIST_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LIST_BOX, GtkListBox))>
  endm
GTK_IS_LIST_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LIST_BOX))>
  endm

;GtkListBox              typedef _GtkListBox

define GTK_TYPE_LIST_BOX_ROW <gtk_list_box_row_get_type ()>
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

_GtkListBoxRow          struct
parent_instance         GtkWidget <>
_GtkListBoxRow          ends
GtkListBoxRow           typedef _GtkListBoxRow

_GtkListBoxRowClass     struct
parent_class            GtkWidgetClass <>
activate                proc :ptr
padding                 gpointer 8 dup(?)
_GtkListBoxRowClass     ends
GtkListBoxRowClass      typedef _GtkListBoxRowClass

CALLBACK(GtkListBoxFilterFunc, :ptr, :gpointer)
CALLBACK(GtkListBoxSortFunc, :ptr, :ptr, :gpointer)
CALLBACK(GtkListBoxUpdateHeaderFunc, :ptr, :ptr, :gpointer)
CALLBACK(GtkListBoxCreateWidgetFunc, :gpointer, :gpointer)

gtk_list_box_row_get_type proto
gtk_list_box_row_new proto

gtk_list_box_row_set_child proto :ptr, :ptr
gtk_list_box_row_get_child proto :ptr

gtk_list_box_row_get_header proto :ptr
gtk_list_box_row_set_header proto :ptr, :ptr
gtk_list_box_row_get_index proto :ptr
gtk_list_box_row_changed proto :ptr

gtk_list_box_row_is_selected proto :ptr

gtk_list_box_row_set_selectable proto :ptr, :gboolean
gtk_list_box_row_get_selectable proto :ptr

gtk_list_box_row_set_activatable proto :ptr, :gboolean
gtk_list_box_row_get_activatable proto :ptr

gtk_list_box_get_type proto
gtk_list_box_prepend proto :ptr, :ptr
gtk_list_box_append proto :ptr, :ptr
gtk_list_box_insert proto :ptr, :ptr, :sdword
gtk_list_box_remove proto :ptr, :ptr
gtk_list_box_get_selected_row proto :ptr
gtk_list_box_get_row_at_index proto :ptr, :sdword
gtk_list_box_get_row_at_y proto :ptr, :sdword
gtk_list_box_select_row proto :ptr, :ptr
gtk_list_box_set_placeholder proto :ptr, :ptr
gtk_list_box_set_adjustment proto :ptr, :ptr
gtk_list_box_get_adjustment proto :ptr

CALLBACK(GtkListBoxForeachFunc, :ptr, :ptr, :gpointer)

gtk_list_box_selected_foreach proto :ptr, :GtkListBoxForeachFunc, :gpointer
gtk_list_box_get_selected_rows proto :ptr
gtk_list_box_unselect_row proto :ptr, :ptr
gtk_list_box_select_all proto :ptr
gtk_list_box_unselect_all proto :ptr

gtk_list_box_set_selection_mode proto :ptr, :GtkSelectionMode
gtk_list_box_get_selection_mode proto :ptr
gtk_list_box_set_filter_func proto :ptr, :GtkListBoxFilterFunc, :gpointer, :GDestroyNotify
gtk_list_box_set_header_func proto :ptr, :GtkListBoxUpdateHeaderFunc, :gpointer, :GDestroyNotify
gtk_list_box_invalidate_filter proto :ptr
gtk_list_box_invalidate_sort proto :ptr
gtk_list_box_invalidate_headers proto :ptr
gtk_list_box_set_sort_func proto :ptr, :GtkListBoxSortFunc, :gpointer, :GDestroyNotify
gtk_list_box_set_activate_on_single_click proto :ptr, :gboolean
gtk_list_box_get_activate_on_single_click proto :ptr
gtk_list_box_drag_unhighlight_row proto :ptr
gtk_list_box_drag_highlight_row proto :ptr, :ptr
gtk_list_box_new proto

gtk_list_box_bind_model proto :ptr, :ptr, :GtkListBoxCreateWidgetFunc, :gpointer, :GDestroyNotify
gtk_list_box_set_show_separators proto :ptr, :gboolean
gtk_list_box_get_show_separators proto :ptr

endif

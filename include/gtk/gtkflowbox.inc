ifndef __GTK_FLOW_BOX_H__
define __GTK_FLOW_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_FLOW_BOX <gtk_flow_box_get_type ()>
GTK_FLOW_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FLOW_BOX, GtkFlowBox))>
  endm
GTK_IS_FLOW_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FLOW_BOX))>
  endm

;GtkFlowBox              typedef _GtkFlowBox

define GTK_TYPE_FLOW_BOX_CHILD <gtk_flow_box_child_get_type ()>
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

_GtkFlowBoxChild        struct
parent_instance         GtkWidget <>
_GtkFlowBoxChild        ends
GtkFlowBoxChild         typedef _GtkFlowBoxChild

_GtkFlowBoxChildClass   struct
parent_class            GtkWidgetClass <>
activate                proc :ptr
padding                 gpointer 8 dup(?)
_GtkFlowBoxChildClass   ends
GtkFlowBoxChildClass    typedef _GtkFlowBoxChildClass

CALLBACK(GtkFlowBoxCreateWidgetFunc, :gpointer, :gpointer)

gtk_flow_box_child_get_type proto
gtk_flow_box_child_new proto
gtk_flow_box_child_set_child proto :ptr, :ptr
gtk_flow_box_child_get_child proto :ptr
gtk_flow_box_child_get_index proto :ptr
gtk_flow_box_child_is_selected proto :ptr
gtk_flow_box_child_changed proto :ptr
gtk_flow_box_get_type proto
gtk_flow_box_new proto
gtk_flow_box_bind_model proto :ptr, :ptr, :GtkFlowBoxCreateWidgetFunc, :gpointer, :GDestroyNotify

gtk_flow_box_set_homogeneous proto :ptr, :gboolean
gtk_flow_box_get_homogeneous proto :ptr
gtk_flow_box_set_row_spacing proto :ptr, :guint
gtk_flow_box_get_row_spacing proto :ptr

gtk_flow_box_set_column_spacing proto :ptr, :guint
gtk_flow_box_get_column_spacing proto :ptr

gtk_flow_box_set_min_children_per_line proto :ptr, :guint
gtk_flow_box_get_min_children_per_line proto :ptr

gtk_flow_box_set_max_children_per_line proto :ptr, :guint
gtk_flow_box_get_max_children_per_line proto :ptr
gtk_flow_box_set_activate_on_single_click proto :ptr, :gboolean
gtk_flow_box_get_activate_on_single_click proto :ptr

gtk_flow_box_prepend proto :ptr, :ptr
gtk_flow_box_append proto :ptr, :ptr
gtk_flow_box_insert proto :ptr, :ptr, :sdword
gtk_flow_box_remove proto :ptr, :ptr
gtk_flow_box_get_child_at_index proto :ptr, :sdword

gtk_flow_box_get_child_at_pos proto :ptr, :sdword, :sdword

CALLBACK(GtkFlowBoxForeachFunc, :ptr, :ptr, :gpointer)

gtk_flow_box_selected_foreach proto :ptr, :GtkFlowBoxForeachFunc, :gpointer
gtk_flow_box_get_selected_children proto :ptr
gtk_flow_box_select_child proto :ptr, :ptr
gtk_flow_box_unselect_child proto :ptr, :ptr
gtk_flow_box_select_all proto :ptr
gtk_flow_box_unselect_all proto :ptr
gtk_flow_box_set_selection_mode proto :ptr, :GtkSelectionMode
gtk_flow_box_get_selection_mode proto :ptr
gtk_flow_box_set_hadjustment proto :ptr, :ptr
gtk_flow_box_set_vadjustment proto :ptr, :ptr

CALLBACK(GtkFlowBoxFilterFunc, :ptr, :gpointer)

gtk_flow_box_set_filter_func proto :ptr, :GtkFlowBoxFilterFunc, :gpointer, :GDestroyNotify
gtk_flow_box_invalidate_filter proto :ptr

CALLBACK(GtkFlowBoxSortFunc, :ptr, :ptr, :gpointer)

gtk_flow_box_set_sort_func proto :ptr, :GtkFlowBoxSortFunc, :gpointer, :GDestroyNotify
gtk_flow_box_invalidate_sort proto :ptr

endif

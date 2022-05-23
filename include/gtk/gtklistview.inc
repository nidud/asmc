ifndef __GTK_LIST_VIEW_H__
define __GTK_LIST_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtklistbase.inc

define GTK_TYPE_LIST_VIEW  <gtk_list_view_get_type>
GTK_LIST_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LIST_VIEW, GtkListView))>
  endm
GTK_LIST_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_LIST_VIEW, GtkListViewClass))>
  endm
GTK_IS_LIST_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LIST_VIEW))>
  endm
GTK_IS_LIST_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LIST_VIEW))>
  endm
GTK_LIST_VIEW_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LIST_VIEW, GtkListViewClass))>
  endm

;GtkListView             typedef _GtkListView
;GtkListViewClass        typedef _GtkListViewClass

gtk_list_view_get_type proto
gtk_list_view_new proto :ptr, :ptr
gtk_list_view_get_model proto :ptr
gtk_list_view_set_model proto :ptr, :ptr
gtk_list_view_set_factory proto :ptr, :ptr
gtk_list_view_get_factory proto :ptr
gtk_list_view_set_show_separators proto :ptr, :gboolean
gtk_list_view_get_show_separators proto :ptr
gtk_list_view_set_single_click_activate proto :ptr, :gboolean
gtk_list_view_get_single_click_activate proto :ptr
gtk_list_view_set_enable_rubberband proto :ptr, :gboolean
gtk_list_view_get_enable_rubberband proto :ptr

endif

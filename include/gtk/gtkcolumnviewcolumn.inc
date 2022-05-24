ifndef __GTK_COLUMN_VIEW_COLUMN_H__
define __GTK_COLUMN_VIEW_COLUMN_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcolumnview.inc
include gtk/gtksorter.inc

define GTK_TYPE_COLUMN_VIEW_COLUMN <gtk_column_view_column_get_type ()>
GTK_COLUMN_VIEW_COLUMN macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_COLUMN_VIEW_COLUMN, GtkColumnViewColumn))>
  endm
GTK_COLUMN_VIEW_COLUMN_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_COLUMN_VIEW_COLUMN, GtkColumnViewColumnClass))>
  endm
GTK_IS_COLUMN_VIEW_COLUMN macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_COLUMN_VIEW_COLUMN))>
  endm
GTK_IS_COLUMN_VIEW_COLUMN_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_COLUMN_VIEW_COLUMN))>
  endm
GTK_COLUMN_VIEW_COLUMN_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_COLUMN_VIEW_COLUMN, GtkColumnViewColumnClass))>
  endm

;GtkColumnViewColumnClass typedef _GtkColumnViewColumnClass

gtk_column_view_column_get_type proto

gtk_column_view_column_new proto :ptr, :ptr

gtk_column_view_column_get_column_view proto :ptr
gtk_column_view_column_set_factory proto :ptr, :ptr
gtk_column_view_column_get_factory proto :ptr

gtk_column_view_column_set_title proto :ptr, :ptr
gtk_column_view_column_get_title proto :ptr

gtk_column_view_column_set_sorter proto :ptr, :ptr
gtk_column_view_column_get_sorter proto :ptr

gtk_column_view_column_set_visible proto :ptr, :gboolean
gtk_column_view_column_get_visible proto :ptr

gtk_column_view_column_set_header_menu proto :ptr, :ptr
gtk_column_view_column_get_header_menu proto :ptr

gtk_column_view_column_set_fixed_width proto :ptr, :sdword
gtk_column_view_column_get_fixed_width proto :ptr

gtk_column_view_column_set_resizable proto :ptr, :gboolean
gtk_column_view_column_get_resizable proto :ptr

gtk_column_view_column_set_expand proto :ptr, :gboolean
gtk_column_view_column_get_expand proto :ptr

endif

ifndef __GTK_COLUMN_VIEW_H__
define __GTK_COLUMN_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc
include gtk/gtksortlistmodel.inc
include gtk/gtkselectionmodel.inc
include gtk/gtksorter.inc

define GTK_TYPE_COLUMN_VIEW <gtk_column_view_get_type ()>
GTK_COLUMN_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_COLUMN_VIEW, GtkColumnView))>
  endm
GTK_COLUMN_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_COLUMN_VIEW, GtkColumnViewClass))>
  endm
GTK_IS_COLUMN_VIEW macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_COLUMN_VIEW))>
  endm
GTK_IS_COLUMN_VIEW_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_COLUMN_VIEW))>
  endm
GTK_COLUMN_VIEW_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_COLUMN_VIEW, GtkColumnViewClass))>
  endm


;GtkColumnView           typedef _GtkColumnView
;GtkColumnViewClass      typedef _GtkColumnViewClass

;GtkColumnViewColumn     typedef _GtkColumnViewColumn

gtk_column_view_get_type proto

gtk_column_view_new proto :ptr

gtk_column_view_get_columns proto :ptr
gtk_column_view_append_column proto :ptr, :ptr
gtk_column_view_remove_column proto :ptr, :ptr
gtk_column_view_insert_column proto :ptr, :guint, :ptr

gtk_column_view_get_model proto :ptr
gtk_column_view_set_model proto :ptr, :ptr

gtk_column_view_get_show_row_separators proto :ptr
gtk_column_view_set_show_row_separators proto :ptr, :gboolean

gtk_column_view_get_show_column_separators proto :ptr
gtk_column_view_set_show_column_separators proto :ptr, :gboolean

gtk_column_view_get_sorter proto :ptr

gtk_column_view_sort_by_column proto :ptr, :ptr, :GtkSortType

gtk_column_view_set_single_click_activate proto :ptr, :gboolean
gtk_column_view_get_single_click_activate proto :ptr

gtk_column_view_set_reorderable proto :ptr, :gboolean
gtk_column_view_get_reorderable proto :ptr

gtk_column_view_set_enable_rubberband proto :ptr, :gboolean
gtk_column_view_get_enable_rubberband proto :ptr

endif

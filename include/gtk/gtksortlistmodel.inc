ifndef __GTK_SORT_LIST_MODEL_H__
define __GTK_SORT_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc
include gtk/gtksorter.inc

define GTK_TYPE_SORT_LIST_MODEL <gtk_sort_list_model_get_type>

gtk_sort_list_model_new proto :ptr, :ptr
gtk_sort_list_model_set_sorter proto :ptr, :ptr
gtk_sort_list_model_get_sorter proto :ptr

gtk_sort_list_model_set_model proto :ptr, :ptr
gtk_sort_list_model_get_model proto :ptr

gtk_sort_list_model_set_incremental proto :ptr, :gboolean
gtk_sort_list_model_get_incremental proto :ptr

gtk_sort_list_model_get_pending proto :ptr

endif

ifndef __GTK_FILTER_LIST_MODEL_H__
define __GTK_FILTER_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkfilter.inc

define GTK_TYPE_FILTER_LIST_MODEL <gtk_filter_list_model_get_type>

gtk_filter_list_model_new proto :ptr, :ptr
gtk_filter_list_model_set_filter proto :ptr, :ptr
gtk_filter_list_model_get_filter proto :ptr
gtk_filter_list_model_set_model proto :ptr, :ptr
gtk_filter_list_model_get_model proto :ptr
gtk_filter_list_model_set_incremental proto :ptr, :gboolean
gtk_filter_list_model_get_incremental proto :ptr
gtk_filter_list_model_get_pending proto :ptr

endif

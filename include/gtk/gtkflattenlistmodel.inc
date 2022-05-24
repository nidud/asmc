ifndef __GTK_FLATTEN_LIST_MODEL_H__
define __GTK_FLATTEN_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

define GTK_TYPE_FLATTEN_LIST_MODEL <gtk_flatten_list_model_get_type ()>

gtk_flatten_list_model_new proto :ptr
gtk_flatten_list_model_set_model proto :ptr, :ptr
gtk_flatten_list_model_get_model proto :ptr
gtk_flatten_list_model_get_model_for_item proto :ptr, :guint

endif

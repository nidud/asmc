ifndef __GTK_SLICE_LIST_MODEL_H__
define __GTK_SLICE_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_SLICE_LIST_MODEL <gtk_slice_list_model_get_type>

gtk_slice_list_model_new proto :ptr, :guint, :guint
gtk_slice_list_model_set_model proto :ptr, :ptr
gtk_slice_list_model_get_model proto :ptr
gtk_slice_list_model_set_offset proto :ptr, :guint
gtk_slice_list_model_get_offset proto :ptr
gtk_slice_list_model_set_size proto :ptr, :guint
gtk_slice_list_model_get_size proto :ptr

endif

ifndef __G_LIST_MODEL_H__
define __G_LIST_MODEL_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_LIST_MODEL <g_list_model_get_type ()>

GListModelInterface     struct
g_iface                 GTypeInterface <>
get_item_type           proc :ptr
get_n_items             proc :ptr
get_item                proc :ptr, :guint
GListModelInterface     ends

g_list_model_get_item_type proto :ptr
g_list_model_get_n_items proto :ptr
g_list_model_get_item proto :ptr, :guint
g_list_model_get_object proto :ptr, :guint
g_list_model_items_changed proto :ptr, :guint, :guint, :guint

endif

ifndef __G_LIST_STORE_H__
define __G_LIST_STORE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_LIST_STORE <g_list_store_get_type ()>

g_list_store_new proto :GType
g_list_store_insert proto :ptr, :guint, :gpointer
g_list_store_insert_sorted proto :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_list_store_sort proto :ptr, :GCompareDataFunc, :gpointer
g_list_store_append proto :ptr, :gpointer
g_list_store_remove proto :ptr, :guint
g_list_store_remove_all proto :ptr
g_list_store_splice proto :ptr, :guint, :guint, :ptr, :guint
g_list_store_find proto :ptr, :gpointer, :ptr
g_list_store_find_with_equal_func proto :ptr, :gpointer, :GEqualFunc, :ptr

endif

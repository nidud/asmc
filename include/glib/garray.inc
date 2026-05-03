ifndef __G_ARRAY_H__
define __G_ARRAY_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

ifndef GCopyFunc
CALLBACKC(GCopyFunc, :gconstpointer, :gpointer)
endif

GArray			STRUC
data			ptr gchar ?
len			guint ?
GArray			ENDS

GByteArray		STRUC
data			ptr guint8 ?
len			guint ?
GByteArray		ENDS

GPtrArray		STRUC
pdata			ptr gpointer ?
len			guint ?
GPtrArray		ENDS

g_array_new proto __cdecl :gboolean, :gboolean, :guint
g_array_steal proto __cdecl :ptr, :ptr
g_array_sized_new proto __cdecl :gboolean, :gboolean, :guint, :guint
g_array_copy proto __cdecl :ptr
g_array_free proto __cdecl :ptr, :gboolean
g_array_ref proto __cdecl :ptr
g_array_unref proto __cdecl :ptr
g_array_get_element_size proto __cdecl :ptr
g_array_append_vals proto __cdecl :ptr, :gconstpointer, :guint
g_array_prepend_vals proto __cdecl :ptr, :gconstpointer, :guint
g_array_insert_vals proto __cdecl :ptr, :guint, :gconstpointer, :guint
g_array_set_size proto __cdecl :ptr, :guint
g_array_remove_index proto __cdecl :ptr, :guint
g_array_remove_index_fast proto __cdecl :ptr, :guint
g_array_remove_range proto __cdecl :ptr, :guint, :guint
g_array_sort proto __cdecl :ptr, :GCompareFunc
g_array_sort_with_data proto __cdecl :ptr, :GCompareDataFunc, :gpointer
g_array_binary_search proto __cdecl :ptr, :gconstpointer, :GCompareFunc, :ptr
g_array_set_clear_func proto __cdecl :ptr, :GDestroyNotify

g_ptr_array_index macro array,index_
	exitm<((array)- GT pdata)[index_]>
	endm
g_ptr_array_new proto __cdecl
g_ptr_array_new_with_free_func proto __cdecl :GDestroyNotify
g_ptr_array_steal proto __cdecl :ptr, :ptr
g_ptr_array_copy proto __cdecl :ptr, :GCopyFunc, :gpointer
g_ptr_array_sized_new proto __cdecl :guint
g_ptr_array_new_full proto __cdecl :guint, :GDestroyNotify
g_ptr_array_free proto __cdecl :ptr, :gboolean
g_ptr_array_ref proto __cdecl :ptr
g_ptr_array_unref proto __cdecl :ptr
g_ptr_array_set_free_func proto __cdecl :ptr, :GDestroyNotify
g_ptr_array_set_size proto __cdecl :ptr, :gint
g_ptr_array_remove_index proto __cdecl :ptr, :guint
g_ptr_array_remove_index_fast proto __cdecl :ptr, :guint
g_ptr_array_steal_index proto __cdecl :ptr, :guint
g_ptr_array_steal_index_fast proto __cdecl :ptr, :guint
g_ptr_array_remove proto __cdecl :ptr, :gpointer
g_ptr_array_remove_fast proto __cdecl :ptr, :gpointer
g_ptr_array_remove_range proto __cdecl :ptr, :guint, :guint
g_ptr_array_add proto __cdecl :ptr, :gpointer
g_ptr_array_extend proto __cdecl :ptr, :ptr, :GCopyFunc, :gpointer
g_ptr_array_extend_and_steal proto __cdecl :ptr, :ptr
g_ptr_array_insert proto __cdecl :ptr, :gint, :gpointer
g_ptr_array_sort proto __cdecl :ptr, :GCompareFunc
g_ptr_array_sort_with_data proto __cdecl :ptr, :GCompareDataFunc, :gpointer
g_ptr_array_foreach proto __cdecl :ptr, :GFunc, :gpointer
g_ptr_array_find proto __cdecl :ptr, :gconstpointer, :ptr
g_ptr_array_find_with_equal_func proto __cdecl :ptr, :gconstpointer, :GEqualFunc, :ptr

g_byte_array_new proto __cdecl
g_byte_array_new_take proto __cdecl :ptr, :gsize
g_byte_array_steal proto __cdecl :ptr, :ptr
g_byte_array_sized_new proto __cdecl :guint
g_byte_array_free proto __cdecl :ptr, :gboolean
g_byte_array_free_to_bytes proto __cdecl :ptr
g_byte_array_ref proto __cdecl :ptr
g_byte_array_unref proto __cdecl :ptr
g_byte_array_append proto __cdecl :ptr, :ptr, :guint
g_byte_array_prepend proto __cdecl :ptr, :ptr, :guint
g_byte_array_set_size proto __cdecl :ptr, :guint
g_byte_array_remove_index proto __cdecl :ptr, :guint
g_byte_array_remove_index_fast proto __cdecl :ptr, :guint
g_byte_array_remove_range proto __cdecl :ptr, :guint, :guint
g_byte_array_sort proto __cdecl :ptr, :GCompareFunc
g_byte_array_sort_with_data proto __cdecl :ptr, :GCompareDataFunc, :gpointer

endif

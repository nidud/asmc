ifndef __G_LIST_H__
define __G_LIST_H__

if NOT defined(__GLIB_H_INSIDE__) AND NOT defined(GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc
include glib/gnode.inc

GList			STRUC
data			gpointer ?
next			ptr GList ?
prev			ptr GList ?
GList			ENDS

g_list_alloc proto __cdecl
g_list_free proto __cdecl :ptr
g_list_free_1 proto __cdecl :ptr

define	g_list_free1 <g_list_free_1>

g_list_free_full proto __cdecl :ptr, :GDestroyNotify
g_list_append proto __cdecl :ptr, :gpointer
g_list_prepend proto __cdecl :ptr, :ptr
g_list_insert proto __cdecl :ptr, :ptr, :gint
g_list_insert_sorted proto __cdecl :ptr, :ptr, :GCompareFunc
g_list_insert_sorted_with_data proto __cdecl :ptr, :ptr, :GCompareDataFunc, :ptr
g_list_insert_before proto __cdecl :ptr, :ptr, :ptr
g_list_insert_before_link proto __cdecl :ptr, :ptr, :ptr
g_list_concat proto __cdecl :ptr, :ptr
g_list_remove proto __cdecl :ptr, :gconstpointer
g_list_remove_all proto __cdecl :ptr, :gconstpointer
g_list_remove_link proto __cdecl :ptr, :ptr
g_list_delete_link proto __cdecl :ptr, :ptr
g_list_reverse proto __cdecl :ptr
g_list_copy proto __cdecl :ptr
g_list_copy_deep proto __cdecl :ptr, :GCopyFunc, :gpointer
g_list_nth proto __cdecl :ptr, :guint
g_list_nth_prev proto __cdecl :ptr, :guint
g_list_find proto __cdecl :ptr, :gconstpointer
g_list_find_custom proto __cdecl :ptr, :gconstpointer, :GCompareFunc
g_list_position proto __cdecl :ptr, :ptr
g_list_index proto __cdecl :ptr, :gconstpointer
g_list_last proto __cdecl :ptr
g_list_first proto __cdecl :ptr
g_list_length proto __cdecl :ptr
g_list_foreach proto __cdecl :ptr, :GFunc, :gpointer
g_list_sort proto __cdecl :ptr, :GCompareFunc
g_list_sort_with_data proto __cdecl :ptr, :GCompareDataFunc, :gpointer
g_list_nth_data proto __cdecl :ptr, :guint
g_clear_list proto __cdecl :ptr, :GDestroyNotify

endif

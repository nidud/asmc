ifndef __G_SLIST_H__
define __G_SLIST_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc
include glib/gnode.inc

GSList			STRUC
data			gpointer ?
next			ptr_t ?
GSList			ENDS

g_slist_alloc proto __cdecl
g_slist_free proto __cdecl :ptr
g_slist_free_1 proto __cdecl :ptr

g_slist_free1 equ <g_slist_free_1>

g_slist_free_full proto __cdecl :ptr, :GDestroyNotify
g_slist_append proto __cdecl :ptr, :ptr
g_slist_prepend proto __cdecl :ptr, :ptr
g_slist_insert proto __cdecl :ptr, :ptr, :gint
g_slist_insert_sorted proto __cdecl :ptr, :ptr, :GCompareFunc
g_slist_insert_sorted_with_data proto __cdecl :ptr, :ptr, :GCompareDataFunc, :ptr
g_slist_insert_before proto __cdecl :ptr, :ptr, :ptr
g_slist_concat proto __cdecl :ptr, :ptr
g_slist_remove proto __cdecl :ptr, :ptr
g_slist_remove_all proto __cdecl :ptr, :ptr
g_slist_remove_link proto __cdecl :ptr, :ptr
g_slist_delete_link proto __cdecl :ptr, :ptr
g_slist_reverse proto __cdecl :ptr
g_slist_copy proto __cdecl :ptr
g_slist_copy_deep proto __cdecl :ptr, :GCopyFunc, :ptr
g_slist_nth proto __cdecl :ptr, :guint
g_slist_find proto __cdecl :ptr, :ptr
g_slist_find_custom proto __cdecl :ptr, :ptr, :GCompareFunc
g_slist_position proto __cdecl :ptr, :ptr
g_slist_index proto __cdecl :ptr, :ptr
g_slist_last proto __cdecl :ptr
g_slist_length proto __cdecl :ptr
g_slist_foreach proto __cdecl :ptr, :GFunc, :ptr
g_slist_sort proto __cdecl :ptr, :GCompareFunc
g_slist_sort_with_data proto __cdecl :ptr, :GCompareDataFunc, :ptr
g_slist_nth_data proto __cdecl :ptr, :guint

endif

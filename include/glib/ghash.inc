ifndef __G_HASH_H__
define __G_HASH_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include glib/glist.inc

CALLBACKC(GHRFunc, :gpointer, :gpointer, :gpointer)

GHashTableIter		STRUC
dummy1			gpointer ?
dummy2			gpointer ?
dummy3			gpointer ?
dummy4			SINT ?
dummy5			gboolean ?
dummy6			gpointer ?
GHashTableIter		ENDS

g_hash_table_new proto __cdecl :GHashFunc, :GEqualFunc
g_hash_table_new_full proto __cdecl :GHashFunc, :GEqualFunc, :GDestroyNotify, :GDestroyNotify
g_hash_table_new_similar proto __cdecl :ptr
g_hash_table_destroy proto __cdecl :ptr
g_hash_table_insert proto __cdecl :ptr, :gpointer, :gpointer
g_hash_table_replace proto __cdecl :ptr, :gpointer, :gpointer
g_hash_table_add proto __cdecl :ptr, :gpointer
g_hash_table_remove proto __cdecl :ptr, :gconstpointer
g_hash_table_remove_all proto __cdecl :ptr
g_hash_table_steal proto __cdecl :ptr, :gconstpointer
g_hash_table_steal_extended proto __cdecl :ptr, :gconstpointer, :ptr, :ptr
g_hash_table_steal_all proto __cdecl :ptr
g_hash_table_lookup proto __cdecl :ptr, :gconstpointer
g_hash_table_contains proto __cdecl :ptr, :gconstpointer
g_hash_table_lookup_extended proto __cdecl :ptr, :gconstpointer, :ptr, :ptr
g_hash_table_foreach proto __cdecl :ptr, :GHFunc, :gpointer
g_hash_table_find proto __cdecl :ptr, :GHRFunc, :gpointer
g_hash_table_foreach_remove proto __cdecl :ptr, :GHRFunc, :gpointer
g_hash_table_foreach_steal proto __cdecl :ptr, :GHRFunc, :gpointer
g_hash_table_size proto __cdecl :ptr
g_hash_table_get_keys proto __cdecl :ptr
g_hash_table_get_values proto __cdecl :ptr
g_hash_table_get_keys_as_array proto __cdecl :ptr, :ptr
g_hash_table_iter_init proto __cdecl :ptr, :ptr
g_hash_table_iter_next proto __cdecl :ptr, :ptr, :ptr
g_hash_table_iter_get_hash_table proto __cdecl :ptr
g_hash_table_iter_remove proto __cdecl :ptr
g_hash_table_iter_replace proto __cdecl :ptr, :gpointer
g_hash_table_iter_steal proto __cdecl :ptr
g_hash_table_ref proto __cdecl :ptr
g_hash_table_unref proto __cdecl :ptr

g_str_equal proto __cdecl :gconstpointer, :gconstpointer
g_str_hash proto __cdecl :gconstpointer
g_int_equal proto __cdecl :gconstpointer, :gconstpointer
g_int_hash proto __cdecl :gconstpointer
g_int64_equal proto __cdecl :gconstpointer, :gconstpointer
g_int64_hash proto __cdecl :gconstpointer
g_double_equal proto __cdecl :gconstpointer, :gconstpointer
g_double_hash proto __cdecl :gconstpointer
g_direct_hash proto __cdecl :gconstpointer
g_direct_equal proto __cdecl :gconstpointer, :gconstpointer

endif

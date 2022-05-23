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

;GHashTable*
g_hash_table_new proto __cdecl \
	     hash_func: GHashFunc,
	key_equal_func: GEqualFunc

;GHashTable*
g_hash_table_new_full proto __cdecl \
	     hash_func: GHashFunc,
	key_equal_func: GEqualFunc,
      key_destroy_func: GDestroyNotify,
    value_destroy_func: GDestroyNotify

;GHashTable
g_hash_table_new_similar proto __cdecl \
      other_hash_table: ptr GHashTable

;void
g_hash_table_destroy proto __cdecl \
	    hash_table: ptr GHashTable

;gboolean
g_hash_table_insert proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gpointer,
		 value: gpointer

;gboolean
g_hash_table_replace proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gpointer,
		 value: gpointer

;gboolean
g_hash_table_add proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gpointer

;gboolean
g_hash_table_remove proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gconstpointer

;void
g_hash_table_remove_all proto __cdecl \
	    hash_table: ptr GHashTable

;gboolean
g_hash_table_steal proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gconstpointer

;gboolean
g_hash_table_steal_extended proto __cdecl \
	    hash_table: ptr GHashTable,
	    lookup_key: gconstpointer,
	    stolen_key: ptr gpointer,
	  stolen_value: ptr gpointer

;void
g_hash_table_steal_all proto __cdecl \
	    hash_table: ptr GHashTable

;gpointer
g_hash_table_lookup proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gconstpointer

;gboolean
g_hash_table_contains proto __cdecl \
	    hash_table: ptr GHashTable,
		   key: gconstpointer

;gboolean
g_hash_table_lookup_extended proto __cdecl \
	    hash_table: ptr GHashTable,
	    lookup_key: gconstpointer,
	      orig_key: ptr gpointer,
		 value: ptr gpointer

;void
g_hash_table_foreach proto __cdecl \
	    hash_table: ptr GHashTable,
		  func: GHFunc,
	     user_data: gpointer

;gpointer
g_hash_table_find proto __cdecl \
	    hash_table: ptr GHashTable,
	     predicate: GHRFunc,
	     user_data: gpointer

;guint
g_hash_table_foreach_remove proto __cdecl \
	    hash_table: ptr GHashTable,
		  func: GHRFunc,
	     user_data: gpointer

;guint
g_hash_table_foreach_steal proto __cdecl \
	    hash_table: ptr GHashTable,
		  func: GHRFunc,
	     user_data: gpointer

;guint
g_hash_table_size proto __cdecl \
	    hash_table: ptr GHashTable

;GList
g_hash_table_get_keys proto __cdecl \
	    hash_table: ptr GHashTable

;GList
g_hash_table_get_values proto __cdecl \
	    hash_table: ptr GHashTable

;gpointer
g_hash_table_get_keys_as_array proto __cdecl \
	    hash_table: ptr GHashTable,
		length: ptr guint


;void
g_hash_table_iter_init proto __cdecl \
		  iter: ptr GHashTableIter,
	    hash_table: ptr GHashTable

;gboolean
g_hash_table_iter_next proto __cdecl \
		  iter: ptr GHashTableIter,
		   key: ptr gpointer,
		 value: ptr gpointer

;GHashTable*
g_hash_table_iter_get_hash_table proto __cdecl \
		  iter: ptr GHashTableIter

;void
g_hash_table_iter_remove proto __cdecl \
		  iter: ptr GHashTableIter

;void
g_hash_table_iter_replace proto __cdecl \
		  iter: ptr GHashTableIter,
		 value: gpointer

;void
g_hash_table_iter_steal proto __cdecl \
		  iter: ptr GHashTableIter


;GHashTable*
g_hash_table_ref proto __cdecl \
	    hash_table: ptr GHashTable

;void
g_hash_table_unref proto __cdecl \
	    hash_table: ptr GHashTable


g_hash_table_freeze macro hash_table
	exitm<.err>
	endm
g_hash_table_thaw macro hash_table
	exitm<.err>
	endm

;gboolean
g_str_equal proto __cdecl \
		    v1: gconstpointer,
		    v2: gconstpointer

;guint
g_str_hash proto __cdecl \
		     v: gconstpointer


;gboolean
g_int_equal proto __cdecl \
		    v1: gconstpointer,
		    v2: gconstpointer

;guint
g_int_hash proto __cdecl \
		     v: gconstpointer


;gboolean
g_int64_equal proto __cdecl \
		    v1: gconstpointer,
		    v2: gconstpointer

;guint
g_int64_hash proto __cdecl \
		     v: gconstpointer


;gboolean
g_double_equal proto __cdecl \
		    v1: gconstpointer,
		    v2: gconstpointer

;guint
g_double_hash proto __cdecl \
		     v: gconstpointer


;guint
g_direct_hash proto __cdecl \
		     v: gconstpointer

;gboolean
g_direct_equal proto __cdecl \
		    v1: gconstpointer,
		    v2: gconstpointer


endif

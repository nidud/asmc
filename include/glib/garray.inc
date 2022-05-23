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

g_array_append_val macro a,v
	exitm<.err>
	endm
g_array_prepend_val macro a,v
	exitm<.err>
	endm
g_array_insert_val macro a,i,v
	exitm<.err>
	endm
g_array_index macro a,t,i
	exitm<.err>
	endm

;GArray*
g_array_new proto __cdecl \
       zero_terminated: gboolean,
		clear_: gboolean,
	  element_size: guint

;gpointer
g_array_steal proto __cdecl \
		 array: ptr GArray,
		   len: ptr gsize

;GArray*
g_array_sized_new proto __cdecl \
       zero_terminated: gboolean,
		clear_: gboolean,
	  element_size: guint,
	 reserved_size: guint

;GArray*
g_array_copy proto __cdecl \
		 array: ptr GArray

;gchar*
g_array_free proto __cdecl \
		 array: ptr GArray,
	  free_segment: gboolean

;GArray
g_array_ref proto __cdecl \
		 array: ptr GArray

;void
g_array_unref proto __cdecl \
		 array: ptr GArray

;guint
g_array_get_element_size proto __cdecl \
		 array: ptr GArray

;GArray*
g_array_append_vals proto __cdecl \
		 array: ptr GArray,
		  data: gconstpointer,
		   len: guint

;GArray*
g_array_prepend_vals proto __cdecl \
		 array: ptr GArray,
		  data: gconstpointer,
		   len: guint

;GArray*
g_array_insert_vals proto __cdecl \
		 array: ptr GArray,
		index_: guint,
		  data: gconstpointer,
		   len: guint

;GArray*
g_array_set_size proto __cdecl \
		 array: ptr GArray,
		length: guint

;GArray*
g_array_remove_index proto __cdecl \
		 array: ptr GArray,
		index_: guint

;GArray*
g_array_remove_index_fast proto __cdecl \
		 array: ptr GArray,
		index_: guint

;GArray*
g_array_remove_range proto __cdecl \
		 array: ptr GArray,
		index_: guint,
		length: guint

;void
g_array_sort proto __cdecl \
		 array: ptr GArray,
	  compare_func: GCompareFunc

;void
g_array_sort_with_data proto __cdecl \
		 array: ptr GArray,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

;gboolean
g_array_binary_search proto __cdecl \
		 array: ptr GArray,
		target: gconstpointer,
	  compare_func: GCompareFunc,
       out_match_index: ptr guint

;void
g_array_set_clear_func proto __cdecl \
		 array: ptr GArray,
	    clear_func: GDestroyNotify


;; Resizable pointer array.  This interface is much less complicated
;; than the above.  Add appends a pointer.  Remove fills any cleared
;; spot and shortens the array. remove_fast will again distort order.
;;
g_ptr_array_index macro array,index_
	exitm<((array)- GT pdata)[index_]>
	endm
;GPtrArray*
g_ptr_array_new proto __cdecl
;GPtrArray*
g_ptr_array_new_with_free_func proto __cdecl \
     element_free_func: GDestroyNotify

;gpointer*
g_ptr_array_steal proto __cdecl \
		 array: ptr GPtrArray,
		   len: ptr gsize

;GPtrArray
g_ptr_array_copy proto __cdecl \
		 array: ptr GPtrArray,
		  func: GCopyFunc,
	     user_data: gpointer

;GPtrArray*
g_ptr_array_sized_new proto __cdecl \
	 reserved_size: guint

;GPtrArray*
g_ptr_array_new_full proto __cdecl \
	 reserved_size: guint,
     element_free_func: GDestroyNotify

;gpointer*
g_ptr_array_free proto __cdecl \
		 array: ptr GPtrArray,
	      free_seg: gboolean

;GPtrArray*
g_ptr_array_ref proto __cdecl \
		 array: ptr GPtrArray

;void
g_ptr_array_unref proto __cdecl \
		 array: ptr GPtrArray

;void
g_ptr_array_set_free_func proto __cdecl \
		 array: ptr GPtrArray,
     element_free_func: GDestroyNotify

;void
g_ptr_array_set_size proto __cdecl \
		 array: ptr GPtrArray,
		length: gint

;gpointer
g_ptr_array_remove_index proto __cdecl \
		 array: ptr GPtrArray,
		index_: guint

;gpointer
g_ptr_array_remove_index_fast proto __cdecl \
		 array: ptr GPtrArray,
		index_: guint

;gpointer
g_ptr_array_steal_index proto __cdecl \
		 array: ptr GPtrArray,
		index_: guint

;gpointer
g_ptr_array_steal_index_fast proto __cdecl \
		 array: ptr GPtrArray,
		index_: guint

;gboolean
g_ptr_array_remove proto __cdecl \
		 array: ptr GPtrArray,
		  data: gpointer

;gboolean
g_ptr_array_remove_fast proto __cdecl \
		 array: ptr GPtrArray,
		  data: gpointer

;GPtrArray
g_ptr_array_remove_range proto __cdecl \
		 array: ptr GPtrArray,
		index_: guint,
		length: guint

;void
g_ptr_array_add proto __cdecl \
		 array: ptr GPtrArray,
		  data: gpointer

;void
g_ptr_array_extend proto __cdecl \
       array_to_extend: ptr GPtrArray,
		 array: ptr GPtrArray,
		  func: GCopyFunc,
	     user_data: gpointer

;void
g_ptr_array_extend_and_steal proto __cdecl \
       array_to_extend: ptr GPtrArray,
		 array: ptr GPtrArray

;void
g_ptr_array_insert proto __cdecl \
		 array: ptr GPtrArray,
		index_: gint,
		  data: gpointer

;void
g_ptr_array_sort proto __cdecl \
		 array: ptr GPtrArray,
	  compare_func: GCompareFunc

;void
g_ptr_array_sort_with_data proto __cdecl \
		 array: ptr GPtrArray,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

;void
g_ptr_array_foreach proto __cdecl \
		 array: ptr GPtrArray,
		  func: GFunc,
	     user_data: gpointer

;gboolean
g_ptr_array_find proto __cdecl \
	      haystack: ptr GPtrArray,
		needle: gconstpointer,
		index_: ptr guint

;gboolean
g_ptr_array_find_with_equal_func proto __cdecl \
	      haystack: ptr GPtrArray,
		needle: gconstpointer,
	    equal_func: GEqualFunc,
		index_: ptr guint



;; Byte arrays, an array of guint8.  Implemented as a GArray,
;; but type-safe.
;;

;GByteArray*
g_byte_array_new proto __cdecl
;GByteArray*
g_byte_array_new_take proto __cdecl \
		  data: ptr guint8,
		   len: gsize

;guint8*
g_byte_array_steal proto __cdecl \
		 array: ptr GByteArray,
		   len: ptr gsize

;GByteArray*
g_byte_array_sized_new proto __cdecl \
	 reserved_size: guint

;guint8*
g_byte_array_free proto __cdecl \
		 array: ptr GByteArray,
	  free_segment: gboolean

;GBytes*
g_byte_array_free_to_bytes proto __cdecl \
		 array: ptr GByteArray

;GByteArray
g_byte_array_ref proto __cdecl \
		 array: ptr GByteArray

;void
g_byte_array_unref proto __cdecl \
		 array: ptr GByteArray

;GByteArray*
g_byte_array_append proto __cdecl \
		 array: ptr GByteArray,
		  data: ptr guint8,
		   len: guint

;GByteArray*
g_byte_array_prepend proto __cdecl \
		 array: ptr GByteArray,
		  data: ptr guint8,
		   len: guint

;GByteArray*
g_byte_array_set_size proto __cdecl \
		 array: ptr GByteArray,
		length: guint

;GByteArray*
g_byte_array_remove_index proto __cdecl \
		 array: ptr GByteArray,
		index_: guint

;GByteArray*
g_byte_array_remove_index_fast proto __cdecl \
		 array: ptr GByteArray,
		index_: guint

;GByteArray*
g_byte_array_remove_range proto __cdecl \
		 array: ptr GByteArray,
		index_: guint,
		length: guint

;void
g_byte_array_sort proto __cdecl \
		 array: ptr GByteArray,
	  compare_func: GCompareFunc

;void
g_byte_array_sort_with_data proto __cdecl \
		 array: ptr GByteArray,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

endif

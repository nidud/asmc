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

;GList*
g_list_alloc proto __cdecl

;void
g_list_free proto __cdecl \
		  list: ptr GList

;void
g_list_free_1 proto __cdecl \
		  list: ptr GList

define	g_list_free1 <g_list_free_1>
;void
g_list_free_full proto __cdecl \
		  list: ptr GList,
	     free_func: GDestroyNotify

;GList*
g_list_append proto __cdecl \
		  list: ptr GList,
		  data: gpointer

;GList*
g_list_prepend proto __cdecl \
		  list: ptr GList,
		  data: gpointer

;GList*
g_list_insert proto __cdecl \
		  list: ptr GList,
		  data: gpointer,
	      position: gint

;GList*
g_list_insert_sorted proto __cdecl \
		  list: ptr GList,
		  data: gpointer,
		  func: GCompareFunc

;GList*
g_list_insert_sorted_with_data proto __cdecl \
		  list: ptr GList,
		  data: gpointer,
		  func: GCompareDataFunc,
	     user_data: gpointer

;GList*
g_list_insert_before proto __cdecl \
		  list: ptr GList,
	       sibling: ptr GList,
		  data: gpointer

;GList*
g_list_insert_before_link proto __cdecl \
		  list: ptr GList,
	       sibling: ptr GList,
		 link_: ptr GList

;GList*
g_list_concat proto __cdecl \
		 list1: ptr GList,
		 list2: ptr GList

;GList*
g_list_remove proto __cdecl \
		  list: ptr GList,
		  data: gconstpointer

;GList*
g_list_remove_all proto __cdecl \
		  list: ptr GList,
		  data: gconstpointer

;GList*
g_list_remove_link proto __cdecl \
		  list: ptr GList,
		 llink: ptr GList

;GList*
g_list_delete_link proto __cdecl \
		  list: ptr GList,
		 link_: ptr GList

;GList*
g_list_reverse proto __cdecl \
		  list: ptr GList

;GList*
g_list_copy proto __cdecl \
		  list: ptr GList


;GList*
g_list_copy_deep proto __cdecl \
		  list: ptr GList,
		  func: GCopyFunc,
	     user_data: gpointer


;GList*
g_list_nth proto __cdecl \
		  list: ptr GList,
		     n: guint

;GList*
g_list_nth_prev proto __cdecl \
		  list: ptr GList,
		     n: guint

;GList*
g_list_find proto __cdecl \
		  list: ptr GList,
		  data: gconstpointer

;GList*
g_list_find_custom proto __cdecl \
		  list: ptr GList,
		  data: gconstpointer,
		  func: GCompareFunc

;gint
g_list_position proto __cdecl \
		  list: ptr GList,
		 llink: ptr GList

;gint
g_list_index proto __cdecl \
		  list: ptr GList,
		  data: gconstpointer

;GList*
g_list_last proto __cdecl \
		  list: ptr GList

;GList*
g_list_first proto __cdecl \
		  list: ptr GList

;guint
g_list_length proto __cdecl \
		  list: ptr GList

;void
g_list_foreach proto __cdecl \
		  list: ptr GList,
		  func: GFunc,
	     user_data: gpointer

;GList*
g_list_sort proto __cdecl \
		  list: ptr GList,
	  compare_func: GCompareFunc

;GList*
g_list_sort_with_data proto __cdecl \
		  list: ptr GList,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

;gpointer
g_list_nth_data proto __cdecl \
		  list: ptr GList,
		     n: guint


;void
g_clear_list proto __cdecl \
	      list_ptr: ptr GList,
	       destroy: GDestroyNotify


g_clear_list macro list_ptr, destroy
	exitm<.err>
	endm
g_list_previous macro list
	exitm<.err>
	endm
g_list_next macro list
	exitm<.err>
	endm

endif

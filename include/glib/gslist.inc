ifndef __G_SLIST_H__
__G_SLIST_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc
include glib/gnode.inc

GSList			STRUC
data			gpointer ?
next			ptr_t ?
GSList			ENDS

;GSList*
g_slist_alloc proto __cdecl
;void
g_slist_free proto __cdecl \
		  list: ptr GSList

;void
g_slist_free_1 proto __cdecl \
		  list: ptr GSList

g_slist_free1		equ <g_slist_free_1>
;void
g_slist_free_full proto __cdecl \
		  list: ptr GSList,
	     free_func: GDestroyNotify

;GSList*
g_slist_append proto __cdecl \
		  list: ptr GSList,
		  data: gpointer

;GSList*
g_slist_prepend proto __cdecl \
		  list: ptr GSList,
		  data: gpointer

;GSList*
g_slist_insert proto __cdecl \
		  list: ptr GSList,
		  data: gpointer,
	      position: gint

;GSList*
g_slist_insert_sorted proto __cdecl \
		  list: ptr GSList,
		  data: gpointer,
		  func: GCompareFunc

;GSList*
g_slist_insert_sorted_with_data proto __cdecl \
		  list: ptr GSList,
		  data: gpointer,
		  func: GCompareDataFunc,
	     user_data: gpointer

;GSList*
g_slist_insert_before proto __cdecl \
		 slist: ptr GSList,
	       sibling: ptr GSList,
		  data: gpointer

;GSList*
g_slist_concat proto __cdecl \
		 list1: ptr GSList,
		 list2: ptr GSList

;GSList*
g_slist_remove proto __cdecl \
		  list: ptr GSList,
		  data: gconstpointer

;GSList*
g_slist_remove_all proto __cdecl \
		  list: ptr GSList,
		  data: gconstpointer

;GSList*
g_slist_remove_link proto __cdecl \
		  list: ptr GSList,
		 link_: ptr GSList

;GSList*
g_slist_delete_link proto __cdecl \
		  list: ptr GSList,
		 link_: ptr GSList

;GSList*
g_slist_reverse proto __cdecl \
		  list: ptr GSList

;GSList*
g_slist_copy proto __cdecl \
		  list: ptr GSList

;GSList*
g_slist_copy_deep proto __cdecl \
		  list: ptr GSList,
		  func: GCopyFunc,
	     user_data: gpointer

;GSList*
g_slist_nth proto __cdecl \
		  list: ptr GSList,
		     n: guint

;GSList*
g_slist_find proto __cdecl \
		  list: ptr GSList,
		  data: gconstpointer

;GSList*
g_slist_find_custom proto __cdecl \
		  list: ptr GSList,
		  data: gconstpointer,
		  func: GCompareFunc

;gint
g_slist_position proto __cdecl \
		  list: ptr GSList,
		 llink: ptr GSList

;gint
g_slist_index proto __cdecl \
		  list: ptr GSList,
		  data: gconstpointer

;GSList*
g_slist_last proto __cdecl \
		  list: ptr GSList

;guint
g_slist_length proto __cdecl \
		  list: ptr GSList

;void
g_slist_foreach proto __cdecl \
		  list: ptr GSList,
		  func: GFunc,
	     user_data: gpointer

;GSList*
g_slist_sort proto __cdecl \
		  list: ptr GSList,
	  compare_func: GCompareFunc

;GSList*
g_slist_sort_with_data proto __cdecl \
		  list: ptr GSList,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

;gpointer
g_slist_nth_data proto __cdecl \
		  list: ptr GSList,
		     n: guint


g_slist_next macro slist
	exitm<((slist) ? (((GSList *)(slist))- GT next) : NULL)>
	endm

endif

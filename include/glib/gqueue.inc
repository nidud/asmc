ifndef __G_QUEUE_H__
define __G_QUEUE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/glist.inc

GQueue			STRUC
head			ptr GList ?
tail			ptr GList ?
length			guint ?
GQueue			ENDS

define G_QUEUE_INIT <{ NULL, NULL, 0 }>

;GQueue*
g_queue_new proto __cdecl
;void
g_queue_free proto __cdecl \
		 queue: ptr GQueue

;void
g_queue_free_full proto __cdecl \
		 queue: ptr GQueue,
	     free_func: GDestroyNotify

;void
g_queue_init proto __cdecl \
		 queue: ptr GQueue

;void
g_queue_clear proto __cdecl \
		 queue: ptr GQueue

;gboolean
g_queue_is_empty proto __cdecl \
		 queue: ptr GQueue

;void
g_queue_clear_full proto __cdecl \
		 queue: ptr GQueue,
	     free_func: GDestroyNotify

;guint
g_queue_get_length proto __cdecl \
		 queue: ptr GQueue

;void
g_queue_reverse proto __cdecl \
		 queue: ptr GQueue

;GQueue
g_queue_copy proto __cdecl \
		 queue: ptr GQueue

;void
g_queue_foreach proto __cdecl \
		 queue: ptr GQueue,
		  func: GFunc,
	     user_data: gpointer

;GList
g_queue_find proto __cdecl \
		 queue: ptr GQueue,
		  data: gconstpointer

;GList
g_queue_find_custom proto __cdecl \
		 queue: ptr GQueue,
		  data: gconstpointer,
		  func: GCompareFunc

;void
g_queue_sort proto __cdecl \
		 queue: ptr GQueue,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer


;void
g_queue_push_head proto __cdecl \
		 queue: ptr GQueue,
		  data: gpointer

;void
g_queue_push_tail proto __cdecl \
		 queue: ptr GQueue,
		  data: gpointer

;void
g_queue_push_nth proto __cdecl \
		 queue: ptr GQueue,
		  data: gpointer,
		     n: gint

;gpointer
g_queue_pop_head proto __cdecl \
		 queue: ptr GQueue

;gpointer
g_queue_pop_tail proto __cdecl \
		 queue: ptr GQueue

;gpointer
g_queue_pop_nth proto __cdecl \
		 queue: ptr GQueue,
		     n: guint

;gpointer
g_queue_peek_head proto __cdecl \
		 queue: ptr GQueue

;gpointer
g_queue_peek_tail proto __cdecl \
		 queue: ptr GQueue

;gpointer
g_queue_peek_nth proto __cdecl \
		 queue: ptr GQueue,
		     n: guint

;gint
g_queue_index proto __cdecl \
		 queue: ptr GQueue,
		  data: gconstpointer

;gboolean
g_queue_remove proto __cdecl \
		 queue: ptr GQueue,
		  data: gconstpointer

;guint
g_queue_remove_all proto __cdecl \
		 queue: ptr GQueue,
		  data: gconstpointer

;void
g_queue_insert_before proto __cdecl \
		 queue: ptr GQueue,
	       sibling: ptr GList,
		  data: gpointer

;void
g_queue_insert_before_link proto __cdecl \
		 queue: ptr GQueue,
	       sibling: ptr GList,
		 link_: ptr GList

;void
g_queue_insert_after proto __cdecl \
		 queue: ptr GQueue,
	       sibling: ptr GList,
		  data: gpointer

;void
g_queue_insert_after_link proto __cdecl \
		 queue: ptr GQueue,
	       sibling: ptr GList,
		 link_: ptr GList

;void
g_queue_insert_sorted proto __cdecl \
		 queue: ptr GQueue,
		  data: gpointer,
		  func: GCompareDataFunc,
	     user_data: gpointer


;void
g_queue_push_head_link proto __cdecl \
		 queue: ptr GQueue,
		 link_: ptr GList

;void
g_queue_push_tail_link proto __cdecl \
		 queue: ptr GQueue,
		 link_: ptr GList

;void
g_queue_push_nth_link proto __cdecl \
		 queue: ptr GQueue,
		     n: gint,
		 link_: ptr GList

;GList*
g_queue_pop_head_link proto __cdecl \
		 queue: ptr GQueue

;GList*
g_queue_pop_tail_link proto __cdecl \
		 queue: ptr GQueue

;GList*
g_queue_pop_nth_link proto __cdecl \
		 queue: ptr GQueue,
		     n: guint

;GList*
g_queue_peek_head_link proto __cdecl \
		 queue: ptr GQueue

;GList*
g_queue_peek_tail_link proto __cdecl \
		 queue: ptr GQueue

;GList*
g_queue_peek_nth_link proto __cdecl \
		 queue: ptr GQueue,
		     n: guint

;gint
g_queue_link_index proto __cdecl \
		 queue: ptr GQueue,
		 link_: ptr GList

;void
g_queue_unlink proto __cdecl \
		 queue: ptr GQueue,
		 link_: ptr GList

;void
g_queue_delete_link proto __cdecl \
		 queue: ptr GQueue,
		 link_: ptr GList


endif

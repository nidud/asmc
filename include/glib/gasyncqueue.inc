ifndef __G_ASYNCQUEUE_H__
define __G_ASYNCQUEUE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gthread.inc

;GAsyncQueue
g_async_queue_new proto __cdecl
;GAsyncQueue
g_async_queue_new_full proto __cdecl \
	item_free_func: GDestroyNotify

;void
g_async_queue_lock proto __cdecl \
		 queue: ptr GAsyncQueue

;void
g_async_queue_unlock proto __cdecl \
		 queue: ptr GAsyncQueue

;GAsyncQueue
g_async_queue_ref proto __cdecl \
		 queue: ptr GAsyncQueue

;void
g_async_queue_unref proto __cdecl \
		 queue: ptr GAsyncQueue


;void
g_async_queue_ref_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue


;void
g_async_queue_unref_and_unlock proto __cdecl \
		 queue: ptr GAsyncQueue


;void
g_async_queue_push proto __cdecl \
		 queue: ptr GAsyncQueue,
		  data: gpointer

;void
g_async_queue_push_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
		  data: gpointer

;void
g_async_queue_push_sorted proto __cdecl \
		 queue: ptr GAsyncQueue,
		  data: gpointer,
		  func: GCompareDataFunc,
	     user_data: gpointer

;void
g_async_queue_push_sorted_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
		  data: gpointer,
		  func: GCompareDataFunc,
	     user_data: gpointer

;gpointer
g_async_queue_pop proto __cdecl \
		 queue: ptr GAsyncQueue

;gpointer
g_async_queue_pop_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue

;gpointer
g_async_queue_try_pop proto __cdecl \
		 queue: ptr GAsyncQueue

;gpointer
g_async_queue_try_pop_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue

;gpointer
g_async_queue_timeout_pop proto __cdecl \
		 queue: ptr GAsyncQueue,
	       timeout: guint64

;gpointer
g_async_queue_timeout_pop_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
	       timeout: guint64

;gint
g_async_queue_length proto __cdecl \
		 queue: ptr GAsyncQueue

;gint
g_async_queue_length_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue

;void
g_async_queue_sort proto __cdecl \
		 queue: ptr GAsyncQueue,
		  func: GCompareDataFunc,
	     user_data: gpointer

;void
g_async_queue_sort_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
		  func: GCompareDataFunc,
	     user_data: gpointer


;gboolean
g_async_queue_remove proto __cdecl \
		 queue: ptr GAsyncQueue,
		  item: gpointer

;gboolean
g_async_queue_remove_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
		  item: gpointer

;void
g_async_queue_push_front proto __cdecl \
		 queue: ptr GAsyncQueue,
		  item: gpointer

;void
g_async_queue_push_front_unlocked proto __cdecl \
		 queue: ptr GAsyncQueue,
		  item: gpointer

endif

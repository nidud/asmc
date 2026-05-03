ifndef __G_ASYNCQUEUE_H__
define __G_ASYNCQUEUE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gthread.inc

g_async_queue_new proto __cdecl
g_async_queue_new_full proto __cdecl :GDestroyNotify
g_async_queue_lock proto __cdecl :ptr
g_async_queue_unlock proto __cdecl :ptr
g_async_queue_ref proto __cdecl :ptr
g_async_queue_unref proto __cdecl :ptr
g_async_queue_ref_unlocked proto __cdecl :ptr
g_async_queue_unref_and_unlock proto __cdecl :ptr
g_async_queue_push proto __cdecl :ptr, :gpointer
g_async_queue_push_unlocked proto __cdecl :ptr, :gpointer
g_async_queue_push_sorted proto __cdecl :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_async_queue_push_sorted_unlocked proto __cdecl :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_async_queue_pop proto __cdecl :ptr
g_async_queue_pop_unlocked proto __cdecl :ptr
g_async_queue_try_pop proto __cdecl :ptr
g_async_queue_try_pop_unlocked proto __cdecl :ptr
g_async_queue_timeout_pop proto __cdecl :ptr, :guint64
g_async_queue_timeout_pop_unlocked proto __cdecl :ptr, :guint64
g_async_queue_length proto __cdecl :ptr
g_async_queue_length_unlocked proto __cdecl :ptr
g_async_queue_sort proto __cdecl :ptr, :GCompareDataFunc, :gpointer
g_async_queue_sort_unlocked proto __cdecl :ptr, :GCompareDataFunc, :gpointer
g_async_queue_remove proto __cdecl :ptr, :gpointer
g_async_queue_remove_unlocked proto __cdecl :ptr, :gpointer
g_async_queue_push_front proto __cdecl :ptr, :gpointer
g_async_queue_push_front_unlocked proto __cdecl :ptr, :gpointer

endif

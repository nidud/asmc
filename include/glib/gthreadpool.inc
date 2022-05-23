ifndef __G_THREADPOOL_H__
define __G_THREADPOOL_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gthread.inc

_GThreadPool            struct
func                    GFunc ?
user_data               gpointer ?
exclusive               gboolean ?
_GThreadPool            ends
GThreadPool             typedef _GThreadPool

g_thread_pool_new proto :GFunc, :gpointer, :gint, :gboolean, :ptr
g_thread_pool_new_full proto :GFunc, :gpointer, :GDestroyNotify, :gint, :gboolean, :ptr
g_thread_pool_free proto :ptr, :gboolean, :gboolean
g_thread_pool_push proto :ptr, :gpointer, :ptr
g_thread_pool_unprocessed proto :ptr
g_thread_pool_set_sort_function proto :ptr, :GCompareDataFunc, :gpointer
g_thread_pool_move_to_front proto :ptr, :gpointer

g_thread_pool_set_max_threads proto :ptr, :gint, :ptr
g_thread_pool_get_max_threads proto :ptr
g_thread_pool_get_num_threads proto :ptr

g_thread_pool_set_max_unused_threads proto :gint
g_thread_pool_get_max_unused_threads proto
g_thread_pool_get_num_unused_threads proto
g_thread_pool_stop_unused_threads proto
g_thread_pool_set_max_idle_time proto :guint
g_thread_pool_get_max_idle_time proto

endif

ifndef __G_QUEUE_H__
define __G_QUEUE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/glist.inc

GQueue			STRUC
head			ptr_t ?
tail			ptr_t ?
length			guint ?
GQueue			ENDS

define G_QUEUE_INIT <{ NULL, NULL, 0 }>

g_queue_new proto __cdecl
g_queue_free proto __cdecl :ptr
g_queue_free_full proto __cdecl :ptr, :GDestroyNotify
g_queue_init proto __cdecl :ptr
g_queue_clear proto __cdecl :ptr
g_queue_is_empty proto __cdecl :ptr
g_queue_clear_full proto __cdecl :ptr, :GDestroyNotify
g_queue_get_length proto __cdecl :ptr
g_queue_reverse proto __cdecl :ptr
g_queue_copy proto __cdecl :ptr
g_queue_foreach proto __cdecl :ptr, :ptr, :ptr
g_queue_find proto __cdecl :ptr, :ptr
g_queue_find_custom proto __cdecl :ptr, :ptr, :GCompareFunc
g_queue_sort proto __cdecl :ptr, :GCompareDataFunc, :ptr
g_queue_push_head proto __cdecl :ptr, :ptr
g_queue_push_tail proto __cdecl :ptr, :ptr
g_queue_push_nth proto __cdecl :ptr, :ptr, :gint
g_queue_pop_head proto __cdecl :ptr
g_queue_pop_tail proto __cdecl :ptr
g_queue_pop_nth proto __cdecl :ptr, :guint
g_queue_peek_head proto __cdecl :ptr
g_queue_peek_tail proto __cdecl :ptr
g_queue_peek_nth proto __cdecl :ptr, :guint
g_queue_index proto __cdecl :ptr, :ptr
g_queue_remove proto __cdecl :ptr, :ptr
g_queue_remove_all proto __cdecl :ptr, :ptr
g_queue_insert_before proto __cdecl :ptr, :ptr, :ptr
g_queue_insert_before_link proto __cdecl :ptr, :ptr, :ptr
g_queue_insert_after proto __cdecl :ptr, :ptr, :ptr
g_queue_insert_after_link proto __cdecl :ptr, :ptr, :ptr
g_queue_insert_sorted proto __cdecl :ptr, :ptr, :GCompareDataFunc, :ptr
g_queue_push_head_link proto __cdecl :ptr, :ptr
g_queue_push_tail_link proto __cdecl :ptr, :ptr
g_queue_push_nth_link proto __cdecl :ptr, :gint, :ptr
g_queue_pop_head_link proto __cdecl :ptr
g_queue_pop_tail_link proto __cdecl :ptr
g_queue_pop_nth_link proto __cdecl :ptr, :guint
g_queue_peek_head_link proto __cdecl :ptr
g_queue_peek_tail_link proto __cdecl :ptr
g_queue_peek_nth_link proto __cdecl :ptr, :guint
g_queue_link_index proto __cdecl :ptr, :ptr
g_queue_unlink proto __cdecl :ptr, :ptr
g_queue_delete_link proto __cdecl :ptr, :ptr

endif

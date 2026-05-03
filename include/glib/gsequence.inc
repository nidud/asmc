ifndef __G_SEQUENCE_H__
define __G_SEQUENCE_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

CALLBACK(GSequenceIterCompareFunc, :ptr, :ptr, :gpointer)

g_sequence_new proto :GDestroyNotify
g_sequence_free proto :ptr
g_sequence_get_length proto :ptr
g_sequence_foreach proto :ptr, :GFunc, :gpointer
g_sequence_foreach_range proto :ptr, :ptr, :GFunc, :gpointer
g_sequence_sort proto :ptr, :GCompareDataFunc, :gpointer
g_sequence_sort_iter proto :ptr, :GSequenceIterCompareFunc, :gpointer
g_sequence_is_empty proto :ptr

g_sequence_get_begin_iter proto :ptr
g_sequence_get_end_iter proto :ptr
g_sequence_get_iter_at_pos proto :ptr, :gint
g_sequence_append proto :ptr, :gpointer
g_sequence_prepend proto :ptr, :gpointer
g_sequence_insert_before proto :ptr, :gpointer
g_sequence_move proto :ptr, :ptr
g_sequence_swap proto :ptr, :ptr
g_sequence_insert_sorted proto :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_sequence_insert_sorted_iter proto :ptr, :gpointer, :GSequenceIterCompareFunc, :gpointer
g_sequence_sort_changed proto :ptr, :GCompareDataFunc, :gpointer
g_sequence_sort_changed_iter proto :ptr, :GSequenceIterCompareFunc, :gpointer
g_sequence_remove proto :ptr
g_sequence_remove_range proto :ptr, :ptr
g_sequence_move_range proto :ptr, :ptr, :ptr
g_sequence_search proto :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_sequence_search_iter proto :ptr, :gpointer, :GSequenceIterCompareFunc, :gpointer
g_sequence_lookup proto :ptr, :gpointer, :GCompareDataFunc, :gpointer
g_sequence_lookup_iter proto :ptr, :gpointer, :GSequenceIterCompareFunc, :gpointer

g_sequence_get proto :ptr
g_sequence_set proto :ptr, :gpointer

g_sequence_iter_is_begin proto :ptr
g_sequence_iter_is_end proto :ptr
g_sequence_iter_next proto :ptr
g_sequence_iter_prev proto :ptr
g_sequence_iter_get_position proto :ptr
g_sequence_iter_move proto :ptr, :gint
g_sequence_iter_get_sequence proto :ptr

g_sequence_iter_compare proto :ptr, :ptr
g_sequence_range_get_midpoint proto :ptr, :ptr

endif

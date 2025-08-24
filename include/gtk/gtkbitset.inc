ifndef __GTK_BITSET_H__
define __GTK_BITSET_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_BITSET <gtk_bitset_get_type ()>

gtk_bitset_get_type proto

gtk_bitset_ref proto :ptr
gtk_bitset_unref proto :ptr

gtk_bitset_contains proto :ptr, :guint
gtk_bitset_is_empty proto :ptr
gtk_bitset_equals proto :ptr, :ptr
gtk_bitset_get_size proto :ptr
gtk_bitset_get_size_in_range proto :ptr, :guint, :guint
gtk_bitset_get_nth proto :ptr, :guint
gtk_bitset_get_minimum proto :ptr
gtk_bitset_get_maximum proto :ptr

gtk_bitset_new_empty proto
gtk_bitset_copy proto :ptr
gtk_bitset_new_range proto :guint, :guint

gtk_bitset_remove_all proto :ptr
gtk_bitset_add proto :ptr, :guint
gtk_bitset_remove proto :ptr, :guint
gtk_bitset_add_range proto :ptr, :guint, :guint
gtk_bitset_remove_range proto :ptr, :guint, :guint
gtk_bitset_add_range_closed proto :ptr, :guint, :guint
gtk_bitset_remove_range_closed proto :ptr, :guint, :guint
gtk_bitset_add_rectangle proto :ptr, :guint, :guint, :guint, :guint
gtk_bitset_remove_rectangle proto :ptr, :guint, :guint, :guint, :guint

gtk_bitset_union proto :ptr, :ptr
gtk_bitset_intersect proto :ptr, :ptr
gtk_bitset_subtract proto :ptr, :ptr
gtk_bitset_difference proto :ptr, :ptr
gtk_bitset_shift_left proto :ptr, :guint
gtk_bitset_shift_right proto :ptr, :guint
gtk_bitset_splice proto :ptr, :guint, :guint, :guint


GtkBitsetIter           struct
private_data            gpointer 10 dup(?)
GtkBitsetIter           ends

gtk_bitset_iter_get_type proto

gtk_bitset_iter_init_first proto :ptr, :ptr, :ptr
gtk_bitset_iter_init_last proto :ptr, :ptr, :ptr
gtk_bitset_iter_init_at proto :ptr, :ptr, :guint, :ptr
gtk_bitset_iter_next proto :ptr, :ptr
gtk_bitset_iter_previous proto :ptr, :ptr
gtk_bitset_iter_get_value proto :ptr
gtk_bitset_iter_is_valid proto :ptr

endif

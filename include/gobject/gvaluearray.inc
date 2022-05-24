ifndef __G_VALUE_ARRAY_H__
define __G_VALUE_ARRAY_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc

define G_TYPE_VALUE_ARRAY <g_value_array_get_type ()>

_GValueArray            struct
n_values                guint ?
values                  ptr GValue ?
n_prealloced            guint ?
_GValueArray            ends
GValueArray             typedef _GValueArray

g_value_array_get_type proto
g_value_array_get_nth proto :ptr, :guint
g_value_array_new proto :guint
g_value_array_free proto :ptr
g_value_array_copy proto :ptr
g_value_array_prepend proto :ptr, :ptr
g_value_array_append proto :ptr, :ptr
g_value_array_insert proto :ptr, :guint, :ptr
g_value_array_remove proto :ptr, :guint
g_value_array_sort proto :ptr, :GCompareFunc
g_value_array_sort_with_data proto :ptr, :GCompareDataFunc, :gpointer

endif

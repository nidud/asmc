ifndef __G_VALUE_ARRAY_H__
__G_VALUE_ARRAY_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc

G_BEGIN_DECLS

G_TYPE_VALUE_ARRAY	equ <g_value_array_get_type>

GValueArray		STRUC
n_values		guint ?
values			ptr_t ?
n_prealloced		guint ?
GValueArray		ENDS

;GType
g_value_array_get_type proto __cdecl
;GValue*
g_value_array_get_nth proto __cdecl \
	   value_array: ptr GValueArray,
		index_: guint
;GValueArray*
g_value_array_new proto __cdecl \
	  n_prealloced: guint

;void
g_value_array_free proto __cdecl \
	   value_array: ptr GValueArray

;GValueArray*
g_value_array_copy proto __cdecl \
	   value_array: ptr GValueArray

g_value_array_prepend proto __cdecl \
	   value_array: ptr GValueArray,
		 value: ptr_t

g_value_array_append proto __cdecl \
	   value_array: ptr GValueArray,
		 value: ptr_t

g_value_array_insert proto __cdecl \
	   value_array: ptr GValueArray,
		 index: guint,
		 value: ptr_t

g_value_array_remove proto __cdecl \
	   value_array: ptr GValueArray,
		 index: guint

g_value_array_sort proto __cdecl \
	   value_array: ptr GValueArray,
	  compare_func: GCompareFunc

g_value_array_sort_with_data proto __cdecl \
	   value_array: ptr GValueArray,
	  compare_func: GCompareDataFunc,
	     user_data: gpointer

G_END_DECLS

endif

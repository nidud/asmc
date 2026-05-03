ifndef __G_ATOMIC_H__
__G_ATOMIC_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_atomic_int_get proto __cdecl :ptr
g_atomic_int_set proto __cdecl :ptr, :gint
g_atomic_int_inc proto __cdecl :ptr
g_atomic_int_dec_and_test proto __cdecl :ptr
g_atomic_int_compare_and_exchange proto __cdecl :ptr, :gint, :gint
g_atomic_int_add proto __cdecl :ptr, :gint
g_atomic_int_and proto __cdecl :ptr, :guint
g_atomic_int_or proto __cdecl :ptr, :guint
g_atomic_int_xor proto __cdecl :ptr, :guint
g_atomic_pointer_get proto __cdecl :ptr
g_atomic_pointer_set proto __cdecl :ptr, :gpointer
g_atomic_pointer_compare_and_exchange proto __cdecl :ptr, :gpointer, :gpointer
g_atomic_pointer_add proto __cdecl :ptr, :gssize
g_atomic_pointer_and proto __cdecl :ptr, :gsize
g_atomic_pointer_or proto __cdecl :ptr, :gsize
g_atomic_pointer_xor proto __cdecl :ptr, :gsize

endif

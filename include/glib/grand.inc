ifndef __G_RAND_H__
define __G_RAND_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_rand_new_with_seed proto __cdecl :guint32
g_rand_new_with_seed_array proto __cdecl :ptr, :guint
g_rand_new proto __cdecl
g_rand_free proto __cdecl :ptr
g_rand_copy proto __cdecl :ptr
g_rand_set_seed proto __cdecl :ptr, :guint32
g_rand_set_seed_array proto __cdecl :ptr, :ptr, :guint
g_rand_int proto __cdecl :ptr
g_rand_int_range proto __cdecl :ptr, :gint32, :gint32
g_rand_double proto __cdecl :ptr
g_rand_double_range proto __cdecl :ptr, :gdouble, :gdouble
g_random_set_seed proto __cdecl :guint32
g_random_int proto __cdecl
g_random_int_range proto __cdecl :gint32, :gint32
g_random_double proto __cdecl
g_random_double_range proto __cdecl :gdouble, :gdouble

endif

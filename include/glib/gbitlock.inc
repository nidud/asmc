ifndef __G_BITLOCK_H__
define __G_BITLOCK_H__

include glib/gtypes.inc

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

g_bit_lock proto __cdecl :ptr, :gint
g_bit_trylock proto __cdecl :ptr, :gint
g_bit_unlock proto __cdecl :ptr, :gint
g_pointer_bit_lock proto __cdecl :ptr, :gint
g_pointer_bit_trylock proto __cdecl :ptr, :gint
g_pointer_bit_unlock proto __cdecl :ptr, :gint

endif

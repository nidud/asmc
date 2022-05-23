ifndef __G_BITLOCK_H__
define __G_BITLOCK_H__

include glib/gtypes.inc

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

;void
g_bit_lock proto __cdecl \
	       address: ptr gint,
	      lock_bit: gint

;gboolean
g_bit_trylock proto __cdecl \
	       address: ptr gint,
	      lock_bit: gint

;void
g_bit_unlock proto __cdecl \
	       address: ptr gint,
	      lock_bit: gint


;void
g_pointer_bit_lock proto __cdecl \
	       address: ptr void,
	      lock_bit: gint

;gboolean
g_pointer_bit_trylock proto __cdecl \
	       address: ptr void,
	      lock_bit: gint

;void
g_pointer_bit_unlock proto __cdecl \
	       address: ptr void,
	      lock_bit: gint


ifdef __GNUC__

g_pointer_bit_lock macro address, lock_bit
	exitm<.err>
	endm
g_pointer_bit_trylock macro address, lock_bit
	exitm<.err>
	endm
g_pointer_bit_unlock macro address, lock_bit
	exitm<.err>
	endm
endif

endif

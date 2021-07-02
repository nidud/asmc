ifndef __G_ATOMIC_H__
__G_ATOMIC_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;gint
g_atomic_int_get proto __cdecl \
		atomic: ptr gint

g_atomic_int_set proto __cdecl \
		atomic: ptr gint,
		newval: gint

g_atomic_int_inc proto __cdecl \
		atomic: ptr gint

;gboolean
g_atomic_int_dec_and_test proto __cdecl \
		atomic: ptr gint

;gboolean
g_atomic_int_compare_and_exchange proto __cdecl \
		atomic: ptr gint,
		oldval: gint,
		newval: gint

;gint
g_atomic_int_add proto __cdecl \
		atomic: ptr gint,
		   val: gint

;guint
g_atomic_int_and proto __cdecl \
		atomic: ptr guint,
		   val: guint

;guint
g_atomic_int_or proto __cdecl \
		atomic: ptr guint,
		   val: guint

;guint
g_atomic_int_xor proto __cdecl \
		atomic: ptr guint,
		   val: guint


;gpointer
g_atomic_pointer_get proto __cdecl \
		atomic: ptr

;void
g_atomic_pointer_set proto __cdecl \
		atomic: ptr,
		newval: gpointer

;gboolean
g_atomic_pointer_compare_and_exchange proto __cdecl \
		atomic: ptr void,
		oldval: gpointer,
		newval: gpointer

;gssize
g_atomic_pointer_add proto __cdecl \
		atomic: ptr,
		   val: gssize

;gsize
g_atomic_pointer_and proto __cdecl \
		atomic: ptr,
		   val: gsize

;gsize
g_atomic_pointer_or proto __cdecl \
		atomic: ptr,
		   val: gsize

;gsize
g_atomic_pointer_xor proto __cdecl \
		atomic: ptr void,
		   val: gsize


if defined(G_ATOMIC_LOCK_FREE) AND defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)

if defined(__ATOMIC_SEQ_CST) AND NOT defined(__clang__)

g_atomic_int_get macro atomic
	exitm<>
	endm

g_atomic_int_set macro atomic, newval
	exitm<>
	endm

if GLIB_SIZEOF_VOID_P EQ 8

g_atomic_pointer_get macro atomic
	exitm<>
	endm

g_atomic_pointer_set macro atomic, newval
	exitm<>
	endm

else

g_atomic_pointer_get macro atomic
	exitm<>
	endm

g_atomic_pointer_set macro atomic, newval
	exitm<>
	endm

endif

else

g_atomic_int_get macro atomic
	exitm<>
	endm

g_atomic_int_set macro atomic, newval
	exitm<>
	endm

g_atomic_pointer_get macro atomic
	exitm<>
	endm

g_atomic_pointer_set macro atomic, newval
	exitm<>
	endm

endif

g_atomic_int_inc macro atomic
	exitm<>
	endm

g_atomic_int_dec_and_test macro atomic
	exitm<>
	endm

g_atomic_int_compare_and_exchange macro atomic, oldval, newval
	exitm<>
	endm

g_atomic_int_add macro atomic, val
	exitm<>
	endm

g_atomic_int_and macro atomic, val
	exitm<>
	endm

g_atomic_int_or macro atomic, val
	exitm<>
	endm

g_atomic_int_xor macro atomic, val
	exitm<>
	endm

g_atomic_pointer_compare_and_exchange macro atomic, oldval, newval
	exitm<>
	endm

g_atomic_pointer_add macro atomic, val
	exitm<>
	endm

g_atomic_pointer_and macro atomic, val
	exitm<>
	endm

g_atomic_pointer_or macro atomic, val
	exitm<>
	endm

g_atomic_pointer_xor macro atomic, val
	exitm<>
	endm

else
if 0
g_atomic_int_get macro atomic
	exitm<>
	endm
g_atomic_int_set macro atomic, newval
	exitm<>
	endm
g_atomic_int_compare_and_exchange macro atomic, oldval, newval
	exitm<>
	endm
g_atomic_int_add macro atomic, val
	exitm<>
	endm
g_atomic_int_and macro atomic, val
	exitm<>
	endm
g_atomic_int_or macro atomic, val
	exitm<>
	endm
g_atomic_int_xor macro atomic, val
	exitm<>
	endm
g_atomic_int_inc macro atomic
	exitm<>
	endm
g_atomic_int_dec_and_test macro atomic
	exitm<>
	endm

g_atomic_pointer_get macro atomic
	exitm<>
	endm
g_atomic_pointer_set macro atomic, newval
	exitm<>
	endm
g_atomic_pointer_compare_and_exchange macro atomic, oldval, newval
	exitm<>
	endm
g_atomic_pointer_add macro atomic, val
	exitm<>
	endm
g_atomic_pointer_and macro atomic, val
	exitm<>
	endm
g_atomic_pointer_or macro atomic, val
	exitm<>
	endm
g_atomic_pointer_xor macro atomic, val
	exitm<>
	endm

endif
endif

endif

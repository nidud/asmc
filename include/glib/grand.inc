ifndef __G_RAND_H__
define __G_RAND_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;GRand*
g_rand_new_with_seed proto __cdecl \
		  seed: guint32

;GRand*
g_rand_new_with_seed_array proto __cdecl \
		  seed: ptr guint32,
	   seed_length: guint

;GRand*
g_rand_new proto __cdecl
;void
g_rand_free proto __cdecl \
		 rand_: ptr GRand

;GRand*
g_rand_copy proto __cdecl \
		 rand_: ptr GRand

;void
g_rand_set_seed proto __cdecl \
		 rand_: ptr GRand,
		  seed: guint32

;void
g_rand_set_seed_array proto __cdecl \
		 rand_: ptr GRand,
		  seed: ptr guint32,
	   seed_length: guint


g_rand_boolean macro rand_
	exitm<((g_rand_int (rand_) AND (1 SHL 15)) NOT = 0)>
	endm

;guint32
g_rand_int proto __cdecl \
		 rand_: ptr GRand

;gint32
g_rand_int_range proto __cdecl \
		 rand_: ptr GRand,
		 begin: gint32,
		  _end: gint32

;gdouble
g_rand_double proto __cdecl \
		 rand_: ptr GRand

;gdouble
g_rand_double_range proto __cdecl \
		 rand_: ptr GRand,
		 begin: gdouble,
		  _end: gdouble

;void
g_random_set_seed proto __cdecl \
		  seed: guint32


g_random_boolean macro
	exitm<((g_random_int () AND (1 SHL 15)) NOT = 0)>
	endm

;guint32
g_random_int proto __cdecl
;gint32
g_random_int_range proto __cdecl \
		 begin: gint32,
		  _end: gint32

;gdouble
g_random_double proto __cdecl
;gdouble
g_random_double_range proto __cdecl \
		 begin: gdouble,
		  _end: gdouble

endif

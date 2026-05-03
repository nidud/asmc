ifndef __G_PRIMES_H__
define __G_PRIMES_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;guint
g_spaced_primes_closest proto __cdecl \
		   num: guint


endif

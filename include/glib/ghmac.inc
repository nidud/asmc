ifndef __G_HMAC_H__
define __G_HMAC_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include gchecksum.inc

g_hmac_new proto __cdecl :GChecksumType, :ptr, :gsize
g_hmac_copy proto __cdecl :ptr
g_hmac_ref proto __cdecl :ptr
g_hmac_unref proto __cdecl :ptr
g_hmac_update proto __cdecl :ptr, :ptr, :gssize
g_hmac_get_string proto __cdecl :ptr
g_hmac_get_digest proto __cdecl :ptr, :ptr, :ptr
g_compute_hmac_for_data proto __cdecl :GChecksumType, :ptr, :gsize, :ptr, :gsize
g_compute_hmac_for_string proto __cdecl :GChecksumType, :ptr, :gsize, :ptr, :gssize
g_compute_hmac_for_bytes proto __cdecl :GChecksumType, :ptr, :ptr

endif

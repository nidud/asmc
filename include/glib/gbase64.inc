ifndef __G_BASE64_H__
define __G_BASE64_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_base64_encode_step proto __cdecl :ptr, :gsize, :gboolean, :ptr, :ptr, :ptr
g_base64_encode_close proto __cdecl :gboolean, :ptr, :ptr, :ptr
g_base64_encode proto __cdecl :ptr, :gsize
g_base64_decode_step proto __cdecl :ptr, :gsize, :ptr, :ptr, :ptr
g_base64_decode proto __cdecl :ptr, :ptr
g_base64_decode_inplace proto __cdecl :ptr, :ptr

endif

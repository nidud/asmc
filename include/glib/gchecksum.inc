ifndef __G_CHECKSUM_H__
define __G_CHECKSUM_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include glib/gbytes.inc

.enum GChecksumType {
    G_CHECKSUM_MD5,
    G_CHECKSUM_SHA1,
    G_CHECKSUM_SHA256,
    G_CHECKSUM_SHA512,
    G_CHECKSUM_SHA384
    }

g_checksum_type_get_length proto WINAPI :GChecksumType
g_checksum_new proto WINAPI :GChecksumType
g_checksum_reset proto WINAPI :ptr
g_checksum_copy proto WINAPI :ptr
g_checksum_free proto WINAPI :ptr
g_checksum_update proto WINAPI :ptr, :ptr, :gssize
g_checksum_get_string proto WINAPI :ptr
g_checksum_get_digest proto WINAPI :ptr, :ptr, :ptr
g_compute_checksum_for_data proto WINAPI :GChecksumType, :ptr, :gsize
g_compute_checksum_for_string proto WINAPI :GChecksumType, :ptr, :gssize
g_compute_checksum_for_bytes proto WINAPI :GChecksumType, :ptr

endif

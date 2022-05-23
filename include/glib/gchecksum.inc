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

;gssize
g_checksum_type_get_length proto WINAPI \
         checksum_type: GChecksumType


;GChecksum
g_checksum_new proto WINAPI \
         checksum_type: GChecksumType

;void
g_checksum_reset proto WINAPI \
              checksum: ptr GChecksum

;GChecksum
g_checksum_copy proto WINAPI \
              checksum: ptr GChecksum

;void
g_checksum_free proto WINAPI \
              checksum: ptr GChecksum

;void
g_checksum_update proto WINAPI \
              checksum: ptr GChecksum,
                  data: ptr guchar,
                length: gssize

;const
g_checksum_get_string proto WINAPI \
              checksum: ptr GChecksum

;void
g_checksum_get_digest proto WINAPI \
              checksum: ptr GChecksum,
                buffer: ptr guint8,
            digest_len: ptr gsize


;gchar
g_compute_checksum_for_data proto WINAPI \
         checksum_type: GChecksumType,
                  data: ptr guchar,
                length: gsize

;gchar
g_compute_checksum_for_string proto WINAPI \
         checksum_type: GChecksumType,
                string: ptr gchar,
                length: gssize


;gchar
g_compute_checksum_for_bytes proto WINAPI \
         checksum_type: GChecksumType,
                  data: ptr GBytes


endif

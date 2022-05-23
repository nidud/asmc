ifndef __G_HMAC_H__
define __G_HMAC_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include gchecksum.inc

;GHmac
g_hmac_new proto __cdecl \
           digest_type: GChecksumType,
                   key: ptr guchar,
               key_len: gsize

;GHmac
g_hmac_copy proto __cdecl \
                  hmac: ptr GHmac

;GHmac
g_hmac_ref proto __cdecl \
                  hmac: ptr GHmac

;void
g_hmac_unref proto __cdecl \
                  hmac: ptr GHmac

;void
g_hmac_update proto __cdecl \
                  hmac: ptr GHmac,
                  data: ptr guchar,
                length: gssize

;const
g_hmac_get_string proto __cdecl \
                  hmac: ptr GHmac

;void
g_hmac_get_digest proto __cdecl \
                  hmac: ptr GHmac,
                buffer: ptr guint8,
            digest_len: ptr gsize


;gchar
g_compute_hmac_for_data proto __cdecl \
           digest_type: GChecksumType,
                   key: ptr guchar,
               key_len: gsize,
                  data: ptr guchar,
                length: gsize

;gchar
g_compute_hmac_for_string proto __cdecl \
           digest_type: GChecksumType,
                   key: ptr guchar,
               key_len: gsize,
                     s: ptr gchar,
                length: gssize

;gchar
g_compute_hmac_for_bytes proto __cdecl \
           digest_type: GChecksumType,
                   key: ptr GBytes,
                  data: ptr GBytes

endif

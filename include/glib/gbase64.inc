ifndef __G_BASE64_H__
define __G_BASE64_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;gsize
g_base64_encode_step proto __cdecl \
                     i: ptr guchar,
                   len: gsize,
           break_lines: gboolean,
                     o: ptr gchar,
                 state: ptr gint,
                  save: ptr gint

;gsize
g_base64_encode_close proto __cdecl \
           break_lines: gboolean,
                     o: ptr gchar,
                 state: ptr gint,
                  save: ptr gint

;gchar*
g_base64_encode proto __cdecl \
                  data: ptr guchar,
                   len: gsize

;gsize
g_base64_decode_step proto __cdecl \
                      : ptr gchar,
                   len: gsize,
                      : ptr guchar,
                 state: ptr gint,
                  save: ptr guint

;guchar
g_base64_decode proto __cdecl \
                  text: ptr gchar,
               out_len: ptr gsize

;guchar
g_base64_decode_inplace proto __cdecl \
                  text: ptr gchar,
               out_len: ptr gsize

endif

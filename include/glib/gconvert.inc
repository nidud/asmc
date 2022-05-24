ifndef __G_CONVERT_H__
define __G_CONVERT_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc

.enum GConvertError {
    G_CONVERT_ERROR_NO_CONVERSION,
    G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
    G_CONVERT_ERROR_FAILED,
    G_CONVERT_ERROR_PARTIAL_INPUT,
    G_CONVERT_ERROR_BAD_URI,
    G_CONVERT_ERROR_NOT_ABSOLUTE_PATH,
    G_CONVERT_ERROR_NO_MEMORY,
    G_CONVERT_ERROR_EMBEDDED_NUL
    }

G_CONVERT_ERROR         equ (g_convert_error_quark ())

;GQuark
g_convert_error_quark proto __cdecl

;GIConv
g_iconv_open proto __cdecl \
            to_codeset: ptr gchar,
          from_codeset: ptr gchar

;gsize
g_iconv proto __cdecl \
             converter: ptr GIConv,
                 inbuf: ptr gchar,
          inbytes_left: ptr gsize,
                outbuf: ptr gchar,
         outbytes_left: ptr gsize

;gint
g_iconv_close proto __cdecl \
             converter: GIConv


;gchar*
g_convert proto __cdecl \
                string: ptr gchar,
                   len: gssize,
            to_codeset: ptr gchar,
          from_codeset: ptr gchar,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError

;gchar*
g_convert_with_iconv proto __cdecl \
                string: ptr gchar,
                   len: gssize,
             converter: GIConv,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError

;gchar*
g_convert_with_fallback proto __cdecl \
                string: ptr gchar,
                   len: gssize,
            to_codeset: ptr gchar,
          from_codeset: ptr gchar,
              fallback: ptr gchar,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError


;gchar*
g_locale_to_utf8 proto __cdecl \
           opsysstring: ptr gchar,
                   len: gssize,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError

;gchar*
g_locale_from_utf8 proto __cdecl \
            utf8string: ptr gchar,
                   len: gssize,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError


;gchar*
g_filename_to_utf8 proto __cdecl \
           opsysstring: ptr gchar,
                   len: gssize,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError

;gchar*
g_filename_from_utf8 proto __cdecl \
            utf8string: ptr gchar,
                   len: gssize,
            bytes_read: ptr gsize,
         bytes_written: ptr gsize,
                 error: ptr GError


;gchar
g_filename_from_uri proto __cdecl \
                   uri: ptr gchar,
              hostname: ptr gchar,
                 error: ptr GError


;gchar
g_filename_to_uri proto __cdecl \
              filename: ptr gchar,
              hostname: ptr gchar,
                 error: ptr GError

;gchar
g_filename_display_name proto __cdecl \
              filename: ptr gchar

;gboolean
g_get_filename_charsets proto __cdecl \
     filename_charsets: ptr gchar


;gchar
g_filename_display_basename proto __cdecl \
              filename: ptr gchar

;gchar
g_uri_list_extract_uris proto __cdecl \
              uri_list: ptr gchar

endif

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

g_convert_error_quark proto __cdecl
g_iconv_open proto __cdecl :ptr, :ptr
g_iconv proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_iconv_close proto __cdecl :ptr
g_convert proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr, :ptr, :ptr
g_convert_with_iconv proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr, :ptr
g_convert_with_fallback proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_locale_to_utf8 proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr
g_locale_from_utf8 proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr
g_filename_to_utf8 proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr
g_filename_from_utf8 proto __cdecl :ptr, :gssize, :ptr, :ptr, :ptr
g_filename_from_uri proto __cdecl :ptr, :ptr, :ptr
g_filename_to_uri proto __cdecl :ptr, :ptr, :ptr
g_filename_display_name proto __cdecl :ptr
g_get_filename_charsets proto __cdecl :ptr
g_filename_display_basename proto __cdecl :ptr
g_uri_list_extract_uris proto __cdecl :ptr

endif

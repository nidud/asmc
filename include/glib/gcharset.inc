ifndef __G_CHARSET_H__
define __G_CHARSET_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;gboolean
g_get_charset proto __cdecl \
               charset: ptr char_t

;gchar
g_get_codeset proto __cdecl
;gboolean
g_get_console_charset proto __cdecl \
               charset: ptr char_t


;const
g_get_language_names proto __cdecl
;const
g_get_language_names_with_category proto __cdecl \
         category_name: ptr gchar

;gchar
g_get_locale_variants proto __cdecl \
                locale: ptr gchar


endif

ifndef __G_HOST_UTILS_H__
define __G_HOST_UTILS_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_hostname_is_non_ascii proto __cdecl \
              hostname: ptr gchar

;gboolean
g_hostname_is_ascii_encoded proto __cdecl \
              hostname: ptr gchar

;gboolean
g_hostname_is_ip_address proto __cdecl \
              hostname: ptr gchar


;gchar
g_hostname_to_ascii proto __cdecl \
              hostname: ptr gchar

;gchar
g_hostname_to_unicode proto __cdecl \
              hostname: ptr gchar

endif

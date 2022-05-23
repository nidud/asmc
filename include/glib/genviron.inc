ifndef __G_ENVIRON_H__
define __G_ENVIRON_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;const
g_getenv proto __cdecl \
              variable: ptr gchar

;gboolean
g_setenv proto __cdecl \
              variable: ptr gchar,
                 value: ptr gchar,
             overwrite: gboolean

;void
g_unsetenv proto __cdecl \
              variable: ptr gchar

;gchar
g_listenv proto __cdecl

;gchar
g_get_environ proto __cdecl
;const
g_environ_getenv proto __cdecl \
                  envp: ptr gchar,
              variable: ptr gchar

;gchar
g_environ_setenv proto __cdecl \
                  envp: ptr gchar,
              variable: ptr gchar,
                 value: ptr gchar,
             overwrite: gboolean

;gchar
g_environ_unsetenv proto __cdecl \
                  envp: ptr gchar,
              variable: ptr gchar


endif

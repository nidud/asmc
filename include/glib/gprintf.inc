ifndef __G_PRINTF_H__
define __G_PRINTF_H__

include glib.inc
include stdio.inc
include stdarg.inc

;gint
g_printf proto _CDecl \
                format: ptr gchar,
                  args: vararg

;gint
g_fprintf proto _CDecl \
                  file: ptr FILE,
                format: ptr gchar,
                  args: vararg

;gint
g_sprintf proto _CDecl \
                string: ptr gchar,
                format: ptr gchar,
                  args: vararg


;gint
g_vprintf proto __cdecl \
                format: ptr gchar,
                argptr: ptr

;gint
g_vfprintf proto __cdecl \
                  file: ptr FILE,
                format: ptr gchar,
                argptr: ptr

;gint
g_vsprintf proto __cdecl \
                string: ptr gchar,
                format: ptr gchar,
                argptr: ptr

;gint
g_vasprintf proto __cdecl \
                string: ptr gchar,
                format: ptr gchar,
                argptr: ptr


endif

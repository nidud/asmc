ifndef __G_ENVIRON_H__
define __G_ENVIRON_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_getenv proto __cdecl :ptr
g_setenv proto __cdecl :ptr, :ptr, :gboolean
g_unsetenv proto __cdecl :ptr
g_listenv proto __cdecl
g_get_environ proto __cdecl
g_environ_getenv proto __cdecl :ptr, :ptr
g_environ_setenv proto __cdecl :ptr, :ptr, :ptr, :gboolean
g_environ_unsetenv proto __cdecl :ptr, :ptr

endif

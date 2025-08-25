ifndef __G_PRINTF_H__
define __G_PRINTF_H__

include glib.inc
include stdio.inc
include stdarg.inc

g_printf proto __Cdecl :ptr, :vararg
g_fprintf proto __Cdecl :ptr, :ptr, :vararg
g_sprintf proto __Cdecl :ptr, :ptr, :vararg
g_vprintf proto __cdecl :ptr, :ptr
g_vfprintf proto __cdecl :ptr, :ptr, :ptr
g_vsprintf proto __cdecl :ptr, :ptr, :ptr
g_vasprintf proto __cdecl :ptr, :ptr, :ptr

endif

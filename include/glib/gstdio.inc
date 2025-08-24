ifndef __G_STDIO_H__
define __G_STDIO_H__

include glib/gprintf.inc

include sys/stat.inc

ifndef _WIN64
GStatBuf typedef _stat32
else
GStatBuf typedef _stati64
endif

if defined(G_OS_UNIX) AND NOT defined(G_STDIO_WRAP_ON_UNIX)

ifndef __GTK_DOC_IGNORE__
define g_chmod   <chmod>
define g_open    <open>
define g_creat   <creat>
define g_rename  <rename>
define g_mkdir   <mkdir>
define g_stat    <stat>
define g_lstat   <lstat>
define g_remove  <remove>
define g_fopen   <fopen>
define g_freopen <freopen>
define g_fsync   <fsync>
define g_utime   <utime>
endif

g_access proto __cdecl :ptr, :SINT
g_chdir proto __cdecl :ptr
g_unlink proto __cdecl :ptr
g_rmdir proto __cdecl :ptr
else
g_access proto __cdecl :ptr, :SINT
g_chmod proto __cdecl :ptr, :SINT
g_open proto __cdecl :ptr, :SINT, :SINT
g_creat proto __cdecl :ptr, :SINT
g_rename proto __cdecl :ptr, :ptr
g_mkdir proto __cdecl :ptr, :SINT
g_chdir proto __cdecl :ptr
g_stat proto __cdecl :ptr, :ptr
g_lstat proto __cdecl :ptr, :ptr
g_unlink proto __cdecl :ptr
g_remove proto __cdecl :ptr
g_rmdir proto __cdecl :ptr
g_fopen proto __cdecl :ptr, :ptr
g_freopen proto __cdecl :ptr, :ptr, :ptr
g_fsync proto __cdecl :gint
g_utime proto __cdecl :ptr, :ptr
endif
g_close proto __cdecl :gint, :ptr

endif

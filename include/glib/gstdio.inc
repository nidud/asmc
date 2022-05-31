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

;int
g_access proto __cdecl \
              filename: ptr gchar,
                  mode: SINT


;int
g_chdir proto __cdecl \
                  path: ptr gchar


;int
g_unlink proto __cdecl \
              filename: ptr gchar


;int
g_rmdir proto __cdecl \
              filename: ptr gchar


else


;int
g_access proto __cdecl \
              filename: ptr gchar,
                  mode: SINT


;int
g_chmod proto __cdecl \
              filename: ptr gchar,
                  mode: SINT


;int
g_open proto __cdecl \
              filename: ptr gchar,
                 flags: SINT,
                  mode: SINT


;int
g_creat proto __cdecl \
              filename: ptr gchar,
                  mode: SINT


;int
g_rename proto __cdecl \
           oldfilename: ptr gchar,
           newfilename: ptr gchar


;int
g_mkdir proto __cdecl \
              filename: ptr gchar,
                  mode: SINT


;int
g_chdir proto __cdecl \
                  path: ptr gchar


;int
g_stat proto __cdecl \
              filename: ptr gchar,
                   buf: ptr GStatBuf


;int
g_lstat proto __cdecl \
              filename: ptr gchar,
                   buf: ptr GStatBuf


;int
g_unlink proto __cdecl \
              filename: ptr gchar


;int
g_remove proto __cdecl \
              filename: ptr gchar


;int
g_rmdir proto __cdecl \
              filename: ptr gchar


;FILE
g_fopen proto __cdecl \
              filename: ptr gchar,
                  mode: ptr gchar


;FILE
g_freopen proto __cdecl \
              filename: ptr gchar,
                  mode: ptr gchar,
                stream: ptr FILE


;gint
g_fsync proto __cdecl \
                    fd: gint

;int
g_utime proto __cdecl \
              filename: ptr gchar,
                   utb: ptr utimbuf


endif

;gboolean
g_close proto __cdecl \
                    fd: gint,
                 error: ptr GError


endif

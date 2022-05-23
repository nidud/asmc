ifndef __G_DIR_H__
define __G_DIR_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc

ifdef G_OS_UNIX
include direct.inc
endif

g_dir_open      proto __cdecl :ptr gchar, :guint, :ptr GError
g_dir_read_name proto __cdecl :ptr GDir
g_dir_rewind    proto __cdecl :ptr GDir
g_dir_close     proto __cdecl :ptr GDir

endif

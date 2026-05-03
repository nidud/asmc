ifndef __G_MAPPED_FILE_H__
define __G_MAPPED_FILE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gbytes.inc
include glib/gerror.inc

g_mapped_file_new proto __cdecl :ptr, :gboolean, :ptr
g_mapped_file_new_from_fd proto __cdecl :gint, :gboolean, :ptr
g_mapped_file_get_length proto __cdecl :ptr
g_mapped_file_get_contents proto __cdecl :ptr
g_mapped_file_get_bytes proto __cdecl :ptr
g_mapped_file_ref proto __cdecl :ptr
g_mapped_file_unref proto __cdecl :ptr
g_mapped_file_free proto __cdecl :ptr

endif

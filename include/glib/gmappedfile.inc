ifndef __G_MAPPED_FILE_H__
define __G_MAPPED_FILE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gbytes.inc
include glib/gerror.inc

;GMappedFile
g_mapped_file_new proto __cdecl \
              filename: ptr gchar,
              writable: gboolean,
                 error: ptr GError

;GMappedFile
g_mapped_file_new_from_fd proto __cdecl \
                    fd: gint,
              writable: gboolean,
                 error: ptr GError

;gsize
g_mapped_file_get_length proto __cdecl \
                  file: ptr GMappedFile

;gchar
g_mapped_file_get_contents proto __cdecl \
                  file: ptr GMappedFile

;GBytes
g_mapped_file_get_bytes proto __cdecl \
                  file: ptr GMappedFile

;GMappedFile
g_mapped_file_ref proto __cdecl \
                  file: ptr GMappedFile

;void
g_mapped_file_unref proto __cdecl \
                  file: ptr GMappedFile


;void
g_mapped_file_free proto __cdecl \
                  file: ptr GMappedFile


endif

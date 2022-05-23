ifndef __G_STRINGCHUNK_H__
define __G_STRINGCHUNK_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;GStringChunk            typedef _GStringChunk

g_string_chunk_new proto :gsize
g_string_chunk_free proto :ptr
g_string_chunk_clear proto :ptr
g_string_chunk_insert proto :ptr, :ptr
g_string_chunk_insert_len proto :ptr, :ptr, :gssize
g_string_chunk_insert_const proto :ptr, :ptr

endif

ifndef __G_FILE_INPUT_STREAM_H__
define __G_FILE_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/ginputstream.inc

define G_TYPE_FILE_INPUT_STREAM         <g_file_input_stream_get_type ()>
G_FILE_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_INPUT_STREAM, GFileInputStream))>
  endm
G_FILE_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_INPUT_STREAM, GFileInputStreamClass))>
  endm
G_IS_FILE_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_INPUT_STREAM))>
  endm
G_IS_FILE_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_INPUT_STREAM))>
  endm
G_FILE_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_INPUT_STREAM, GFileInputStreamClass))>
  endm


GFileInputStream        struct
parent_instance         GInputStream <>
priv                    ptr GFileInputStreamPrivate ?
GFileInputStream        ends

GFileInputStreamClass   struct
parent_class            GInputStreamClass <>
tell                    proc :ptr
can_seek                proc :ptr
seek                    proc :ptr, :goffset, :GSeekType, :ptr, :ptr
query_info              proc :ptr, :ptr, :ptr, :ptr
query_info_async        proc :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
query_info_finish       proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
GFileInputStreamClass   ends

g_file_input_stream_get_type proto
g_file_input_stream_query_info proto :ptr, :ptr, :ptr, :ptr
g_file_input_stream_query_info_async proto :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_file_input_stream_query_info_finish proto :ptr, :ptr, :ptr

endif

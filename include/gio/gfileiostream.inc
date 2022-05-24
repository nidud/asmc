ifndef __G_FILE_IO_STREAM_H__
define __G_FILE_IO_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giostream.inc

define G_TYPE_FILE_IO_STREAM         <g_file_io_stream_get_type ()>
G_FILE_IO_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_IO_STREAM, GFileIOStream))>
  endm
G_FILE_IO_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_IO_STREAM, GFileIOStreamClass))>
  endm
G_IS_FILE_IO_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_IO_STREAM))>
  endm
G_IS_FILE_IO_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_IO_STREAM))>
  endm
G_FILE_IO_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_IO_STREAM, GFileIOStreamClass))>
  endm


;GFileIOStreamPrivate    typedef _GFileIOStreamPrivate

_GFileIOStream          struct
parent_instance         GIOStream <>
priv                    ptr GFileIOStreamPrivate ?
_GFileIOStream          ends
GFileIOStream           typedef _GFileIOStream

_GFileIOStreamClass     struct
parent_class            GIOStreamClass <>
tell                    proc :ptr
can_seek                proc :ptr
seek                    proc :ptr, :goffset, :GSeekType, :ptr, :ptr
can_truncate            proc :ptr
truncate_fn             proc :ptr, :goffset, :ptr, :ptr
query_info              proc :ptr, :ptr, :ptr, :ptr
query_info_async        proc :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
query_info_finish       proc :ptr, :ptr, :ptr
get_etag                proc :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GFileIOStreamClass     ends
GFileIOStreamClass      typedef _GFileIOStreamClass

g_file_io_stream_get_type proto
g_file_io_stream_query_info proto :ptr, :ptr, :ptr, :ptr
g_file_io_stream_query_info_async proto :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_file_io_stream_query_info_finish proto :ptr, :ptr, :ptr
g_file_io_stream_get_etag proto :ptr

endif

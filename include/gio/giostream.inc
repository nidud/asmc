ifndef __G_IO_STREAM_H__
define __G_IO_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/ginputstream.inc
include gio/goutputstream.inc
include gio/gcancellable.inc
include gio/gioerror.inc

define G_TYPE_IO_STREAM         <g_io_stream_get_type>
G_IO_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_IO_STREAM, GIOStream))>
  endm
G_IO_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_IO_STREAM, GIOStreamClass))>
  endm
G_IS_IO_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_IO_STREAM))>
  endm
G_IS_IO_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_IO_STREAM))>
  endm
G_IO_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_IO_STREAM, GIOStreamClass))>
  endm

;GIOStreamPrivate        typedef _GIOStreamPrivate

_GIOStream              struct
parent_instance         GObject <>
priv                    ptr GIOStreamPrivate ?
_GIOStream              ends
GIOStream               typedef _GIOStream

_GIOStreamClass         struct
parent_class            GObjectClass <>
get_input_stream        proc :ptr
get_output_stream       proc :ptr
close_fn                proc :ptr, :ptr, :ptr
close_async             proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
close_finish            proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
_g_reserved8            proc
_g_reserved9            proc
_g_reserved10           proc
_GIOStreamClass         ends
GIOStreamClass          typedef _GIOStreamClass

g_io_stream_get_type proto
g_io_stream_get_input_stream proto :ptr
g_io_stream_get_output_stream proto :ptr
g_io_stream_splice_async proto :ptr, :ptr, :GIOStreamSpliceFlags, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_io_stream_splice_finish proto :ptr, :ptr
g_io_stream_close proto :ptr, :ptr, :ptr
g_io_stream_close_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_io_stream_close_finish proto :ptr, :ptr, :ptr
g_io_stream_is_closed proto :ptr
g_io_stream_has_pending proto :ptr
g_io_stream_set_pending proto :ptr, :ptr
g_io_stream_clear_pending proto :ptr

endif

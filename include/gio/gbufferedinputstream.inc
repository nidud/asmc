ifndef __G_BUFFERED_INPUT_STREAM_H__
define __G_BUFFERED_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gfilterinputstream.inc

define G_TYPE_BUFFERED_INPUT_STREAM         <g_buffered_input_stream_get_type>
G_BUFFERED_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_BUFFERED_INPUT_STREAM, GBufferedInputStream))>
  endm
G_BUFFERED_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_BUFFERED_INPUT_STREAM, GBufferedInputStreamClass))>
  endm
G_IS_BUFFERED_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_BUFFERED_INPUT_STREAM))>
  endm
G_IS_BUFFERED_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_BUFFERED_INPUT_STREAM))>
  endm
G_BUFFERED_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_BUFFERED_INPUT_STREAM, GBufferedInputStreamClass))>
  endm


;GBufferedInputStreamPrivate typedef _GBufferedInputStreamPrivate

_GBufferedInputStream   struct
parent_instance         GFilterInputStream <>
priv                    ptr GBufferedInputStreamPrivate ?
_GBufferedInputStream   ends
GBufferedInputStream    typedef _GBufferedInputStream

_GBufferedInputStreamClass struct
parent_class            GFilterInputStreamClass <>
fill                    proc :ptr, :gssize, :ptr, :ptr
fill_async              proc :ptr, :gssize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
fill_finish             proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GBufferedInputStreamClass ends
GBufferedInputStreamClass typedef _GBufferedInputStreamClass


g_buffered_input_stream_get_type proto
g_buffered_input_stream_new proto :ptr
g_buffered_input_stream_new_sized proto :ptr, :gsize

g_buffered_input_stream_get_buffer_size proto :ptr
g_buffered_input_stream_set_buffer_size proto :ptr, :gsize
g_buffered_input_stream_get_available proto :ptr
g_buffered_input_stream_peek proto :ptr, :ptr, :gsize, :gsize
g_buffered_input_stream_peek_buffer proto :ptr, :ptr

g_buffered_input_stream_fill proto :ptr, :gssize, :ptr, :ptr
g_buffered_input_stream_fill_async proto :ptr, :gssize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_buffered_input_stream_fill_finish proto :ptr, :ptr, :ptr

g_buffered_input_stream_read_byte proto :ptr, :ptr, :ptr

endif

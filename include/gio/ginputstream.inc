ifndef __G_INPUT_STREAM_H__
define __G_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_INPUT_STREAM         <g_input_stream_get_type ()>
G_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_INPUT_STREAM, GInputStream))>
  endm
G_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_INPUT_STREAM, GInputStreamClass))>
  endm
G_IS_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_INPUT_STREAM))>
  endm
G_IS_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_INPUT_STREAM))>
  endm
G_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_INPUT_STREAM, GInputStreamClass))>
  endm


;GInputStreamPrivate     typedef _GInputStreamPrivate

_GInputStream           struct
parent_instance         GObject <>
priv                    ptr GInputStreamPrivate ?
_GInputStream           ends
GInputStream            typedef _GInputStream

_GInputStreamClass      struct
parent_class            GObjectClass <>
read_fn                 proc :ptr, :ptr, :gsize, :ptr, :ptr
skip                    proc :ptr, :gsize, :ptr, :ptr
close_fn                proc :ptr, :ptr, :ptr
read_async              proc :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
read_finish             proc :ptr, :ptr, :ptr
skip_async              proc :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
skip_finish             proc :ptr, :ptr, :ptr
close_async             proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
close_finish            proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GInputStreamClass      ends
GInputStreamClass       typedef _GInputStreamClass

g_input_stream_get_type proto

g_input_stream_read proto :ptr, :ptr, :gsize, :ptr, :ptr
g_input_stream_read_all proto :ptr, :ptr, :gsize, :ptr, :ptr, :ptr
g_input_stream_read_bytes proto :ptr, :gsize, :ptr, :ptr
g_input_stream_skip proto :ptr, :gsize, :ptr, :ptr
g_input_stream_close proto :ptr, :ptr, :ptr
g_input_stream_read_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_input_stream_read_finish proto :ptr, :ptr, :ptr

g_input_stream_read_all_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_input_stream_read_all_finish proto :ptr, :ptr, :ptr, :ptr

g_input_stream_read_bytes_async proto :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_input_stream_read_bytes_finish proto :ptr, :ptr, :ptr
g_input_stream_skip_async proto :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_input_stream_skip_finish proto :ptr, :ptr, :ptr
g_input_stream_close_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_input_stream_close_finish proto :ptr, :ptr, :ptr
g_input_stream_is_closed proto :ptr
g_input_stream_has_pending proto :ptr
g_input_stream_set_pending proto :ptr, :ptr
g_input_stream_clear_pending proto :ptr

endif

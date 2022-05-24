ifndef __G_OUTPUT_STREAM_H__
define __G_OUTPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_OUTPUT_STREAM         <g_output_stream_get_type ()>
G_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_OUTPUT_STREAM, GOutputStream))>
  endm
G_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_OUTPUT_STREAM, GOutputStreamClass))>
  endm
G_IS_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_OUTPUT_STREAM))>
  endm
G_IS_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_OUTPUT_STREAM))>
  endm
G_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_OUTPUT_STREAM, GOutputStreamClass))>
  endm


;GOutputStreamPrivate    typedef _GOutputStreamPrivate

_GOutputStream          struct
parent_instance         GObject <>
priv                    ptr GOutputStreamPrivate ?
_GOutputStream          ends
GOutputStream           typedef _GOutputStream


_GOutputStreamClass     struct
parent_class            GObjectClass <>
write_fn                proc :ptr, :ptr, :gsize, :ptr, :ptr
splice                  proc :ptr, :ptr, :GOutputStreamSpliceFlags, :ptr, :ptr
flush                   proc :ptr, :ptr, :ptr
close_fn                proc :ptr, :ptr, :ptr
write_async             proc :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
write_finish            proc :ptr, :ptr, :ptr
splice_async            proc :ptr, :ptr, :GOutputStreamSpliceFlags, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
splice_finish           proc :ptr, :ptr, :ptr
flush_async             proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
flush_finish            proc :ptr, :ptr, :ptr
close_async             proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
close_finish            proc :ptr, :ptr, :ptr
writev_fn               proc :ptr, :ptr, :gsize, :ptr, :ptr, :ptr
writev_async            proc :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
writev_finish           proc :ptr, :ptr, :ptr, :ptr
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
_g_reserved8            proc
_GOutputStreamClass     ends
GOutputStreamClass      typedef _GOutputStreamClass

g_output_stream_get_type proto
g_output_stream_write proto :ptr, :ptr, :gsize, :ptr, :ptr
g_output_stream_write_all proto :ptr, :ptr, :gsize, :ptr, :ptr, :ptr
g_output_stream_writev proto :ptr, :ptr, :gsize, :ptr, :ptr, :ptr
g_output_stream_writev_all proto :ptr, :ptr, :gsize, :ptr, :ptr, :ptr
g_output_stream_write_bytes proto :ptr, :ptr, :ptr, :ptr
g_output_stream_splice proto :ptr, :ptr, :GOutputStreamSpliceFlags, :ptr, :ptr
g_output_stream_flush proto :ptr, :ptr, :ptr
g_output_stream_close proto :ptr, :ptr, :ptr
g_output_stream_write_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_write_finish proto :ptr, :ptr, :ptr
g_output_stream_write_all_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_write_all_finish proto :ptr, :ptr, :ptr, :ptr
g_output_stream_writev_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_writev_finish proto :ptr, :ptr, :ptr, :ptr
g_output_stream_writev_all_async proto :ptr, :ptr, :gsize, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_writev_all_finish proto :ptr, :ptr, :ptr, :ptr

g_output_stream_write_bytes_async proto :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_write_bytes_finish proto :ptr, :ptr, :ptr
g_output_stream_splice_async proto :ptr, :ptr, :GOutputStreamSpliceFlags, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_splice_finish proto :ptr, :ptr, :ptr
g_output_stream_flush_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_flush_finish proto :ptr, :ptr, :ptr
g_output_stream_close_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_output_stream_close_finish proto :ptr, :ptr, :ptr

g_output_stream_is_closed proto :ptr
g_output_stream_is_closing proto :ptr
g_output_stream_has_pending proto :ptr
g_output_stream_set_pending proto :ptr, :ptr
g_output_stream_clear_pending proto :ptr

endif

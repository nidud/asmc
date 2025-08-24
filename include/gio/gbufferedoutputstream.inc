ifndef __G_BUFFERED_OUTPUT_STREAM_H__
define __G_BUFFERED_OUTPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gfilteroutputstream.inc

define G_TYPE_BUFFERED_OUTPUT_STREAM         <g_buffered_output_stream_get_type ()>
G_BUFFERED_OUTPUT_STREAM macro o
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_BUFFERED_OUTPUT_STREAM, GBufferedOutputStream)>
  endm
G_BUFFERED_OUTPUT_STREAM_CLASS macro k
  exitm<G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_BUFFERED_OUTPUT_STREAM, GBufferedOutputStreamClass)>
  endm
G_IS_BUFFERED_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_BUFFERED_OUTPUT_STREAM))>
  endm
G_IS_BUFFERED_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_BUFFERED_OUTPUT_STREAM))>
  endm
G_BUFFERED_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_BUFFERED_OUTPUT_STREAM, GBufferedOutputStreamClass))>
  endm


GBufferedOutputStream   struct
parent_instance         GFilterOutputStream <>
priv                    ptr GBufferedOutputStreamPrivate ?
GBufferedOutputStream   ends

GBufferedOutputStreamClass struct
parent_class            GFilterOutputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
GBufferedOutputStreamClass ends

g_buffered_output_stream_get_type proto
g_buffered_output_stream_new proto :ptr
g_buffered_output_stream_new_sized proto :ptr, :gsize
g_buffered_output_stream_get_buffer_size proto :ptr
g_buffered_output_stream_set_buffer_size proto :ptr, :gsize
g_buffered_output_stream_get_auto_grow proto :ptr
g_buffered_output_stream_set_auto_grow proto :ptr, :gboolean

endif

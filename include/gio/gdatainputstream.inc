ifndef __G_DATA_INPUT_STREAM_H__
define __G_DATA_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gbufferedinputstream.inc

define G_TYPE_DATA_INPUT_STREAM         <g_data_input_stream_get_type ()>
G_DATA_INPUT_STREAM macro o
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DATA_INPUT_STREAM, GDataInputStream)>
  endm
G_DATA_INPUT_STREAM_CLASS macro k
  exitm<G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DATA_INPUT_STREAM, GDataInputStreamClass)>
  endm
G_IS_DATA_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DATA_INPUT_STREAM))>
  endm
G_IS_DATA_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DATA_INPUT_STREAM))>
  endm
G_DATA_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DATA_INPUT_STREAM, GDataInputStreamClass))>
  endm

GDataInputStream        struct
parent_instance         GBufferedInputStream <>
priv                    ptr GDataInputStreamPrivate ?
GDataInputStream        ends

GDataInputStreamClass   struct
parent_class            GBufferedInputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
GDataInputStreamClass   ends

g_data_input_stream_get_type proto
g_data_input_stream_new proto :ptr

g_data_input_stream_set_byte_order proto :ptr, :GDataStreamByteOrder
g_data_input_stream_get_byte_order proto :ptr
g_data_input_stream_set_newline_type proto :ptr, :GDataStreamNewlineType
g_data_input_stream_get_newline_type proto :ptr
g_data_input_stream_read_byte proto :ptr, :ptr, :ptr
g_data_input_stream_read_int16 proto :ptr, :ptr, :ptr
g_data_input_stream_read_uint16 proto :ptr, :ptr, :ptr
g_data_input_stream_read_int32 proto :ptr, :ptr, :ptr
g_data_input_stream_read_uint32 proto :ptr, :ptr, :ptr
g_data_input_stream_read_int64 proto :ptr, :ptr, :ptr
g_data_input_stream_read_uint64 proto :ptr, :ptr, :ptr
g_data_input_stream_read_line proto :ptr, :ptr, :ptr, :ptr
g_data_input_stream_read_line_utf8 proto :ptr, :ptr, :ptr, :ptr
g_data_input_stream_read_line_async proto :ptr, :gint, :ptr, :GAsyncReadyCallback, :gpointer
g_data_input_stream_read_line_finish proto :ptr, :ptr, :ptr, :ptr
g_data_input_stream_read_line_finish_utf8 proto :ptr, :ptr, :ptr, :ptr
g_data_input_stream_read_until proto :ptr, :ptr, :ptr, :ptr, :ptr
g_data_input_stream_read_until_async proto :ptr, :ptr, :gint, :ptr, :GAsyncReadyCallback, :gpointer
g_data_input_stream_read_until_finish proto :ptr, :ptr, :ptr, :ptr

g_data_input_stream_read_upto proto :ptr, :ptr, :gssize, :ptr, :ptr, :ptr
g_data_input_stream_read_upto_async proto :ptr, :ptr, :gssize, :gint, :ptr, :GAsyncReadyCallback, :gpointer
g_data_input_stream_read_upto_finish proto :ptr, :ptr, :ptr, :ptr

endif

ifndef __G_DATA_OUTPUT_STREAM_H__
define __G_DATA_OUTPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gfilteroutputstream.inc

define G_TYPE_DATA_OUTPUT_STREAM         <g_data_output_stream_get_type>
G_DATA_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DATA_OUTPUT_STREAM, GDataOutputStream))>
  endm
G_DATA_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DATA_OUTPUT_STREAM, GDataOutputStreamClass))>
  endm
G_IS_DATA_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DATA_OUTPUT_STREAM))>
  endm
G_IS_DATA_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DATA_OUTPUT_STREAM))>
  endm
G_DATA_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DATA_OUTPUT_STREAM, GDataOutputStreamClass))>
  endm


;GDataOutputStreamPrivate typedef _GDataOutputStreamPrivate

_GDataOutputStream      struct
parent_instance         GFilterOutputStream <>
priv                    ptr GDataOutputStreamPrivate ?
_GDataOutputStream      ends
GDataOutputStream       typedef _GDataOutputStream

_GDataOutputStreamClass struct
parent_class            GFilterOutputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GDataOutputStreamClass ends
GDataOutputStreamClass  typedef _GDataOutputStreamClass

g_data_output_stream_get_type proto
g_data_output_stream_new proto :ptr

g_data_output_stream_set_byte_order proto :ptr, :GDataStreamByteOrder
g_data_output_stream_get_byte_order proto :ptr

g_data_output_stream_put_byte proto :ptr, :guchar, :ptr, :ptr
g_data_output_stream_put_int16 proto :ptr, :gint16, :ptr, :ptr
g_data_output_stream_put_uint16 proto :ptr, :guint16, :ptr, :ptr
g_data_output_stream_put_int32 proto :ptr, :gint32, :ptr, :ptr
g_data_output_stream_put_uint32 proto :ptr, :guint32, :ptr, :ptr
g_data_output_stream_put_int64 proto :ptr, :gint64, :ptr, :ptr
g_data_output_stream_put_uint64 proto :ptr, :guint64, :ptr, :ptr
g_data_output_stream_put_string proto :ptr, :ptr, :ptr, :ptr

endif

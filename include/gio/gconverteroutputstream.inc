ifndef __G_CONVERTER_OUTPUT_STREAM_H__
define __G_CONVERTER_OUTPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gfilteroutputstream.inc
include gio/gconverter.inc

define G_TYPE_CONVERTER_OUTPUT_STREAM         <g_converter_output_stream_get_type ()>
G_CONVERTER_OUTPUT_STREAM macro o
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_CONVERTER_OUTPUT_STREAM, GConverterOutputStream)>
  endm
G_CONVERTER_OUTPUT_STREAM_CLASS macro k
  exitm<G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_CONVERTER_OUTPUT_STREAM, GConverterOutputStreamClass)>
  endm
G_IS_CONVERTER_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_CONVERTER_OUTPUT_STREAM))>
  endm
G_IS_CONVERTER_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_CONVERTER_OUTPUT_STREAM))>
  endm
G_CONVERTER_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_CONVERTER_OUTPUT_STREAM, GConverterOutputStreamClass))>
  endm


;GConverterOutputStreamPrivate typedef _GConverterOutputStreamPrivate

_GConverterOutputStream struct
parent_instance         GFilterOutputStream <>
priv                    ptr GConverterOutputStreamPrivate ?
_GConverterOutputStream ends
GConverterOutputStream  typedef _GConverterOutputStream

_GConverterOutputStreamClass struct
parent_class            GFilterOutputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GConverterOutputStreamClass ends
GConverterOutputStreamClass typedef _GConverterOutputStreamClass

g_converter_output_stream_get_type proto
g_converter_output_stream_new proto :ptr, :ptr
g_converter_output_stream_get_converter proto :ptr

endif

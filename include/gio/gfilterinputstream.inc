ifndef __G_FILTER_INPUT_STREAM_H__
define __G_FILTER_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/ginputstream.inc

define G_TYPE_FILTER_INPUT_STREAM         <g_filter_input_stream_get_type ()>
G_FILTER_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILTER_INPUT_STREAM, GFilterInputStream))>
  endm
G_FILTER_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILTER_INPUT_STREAM, GFilterInputStreamClass))>
  endm
G_IS_FILTER_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILTER_INPUT_STREAM))>
  endm
G_IS_FILTER_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILTER_INPUT_STREAM))>
  endm
G_FILTER_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILTER_INPUT_STREAM, GFilterInputStreamClass))>
  endm


GFilterInputStream      struct
parent_instance         GInputStream <>
base_stream             ptr GInputStream ?
GFilterInputStream      ends

GFilterInputStreamClass struct
parent_class            GInputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
GFilterInputStreamClass ends

g_filter_input_stream_get_type proto
g_filter_input_stream_get_base_stream proto :ptr
g_filter_input_stream_get_close_base_stream proto :ptr
g_filter_input_stream_set_close_base_stream proto :ptr, :gboolean

endif

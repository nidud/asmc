ifndef __G_MEMORY_OUTPUT_STREAM_H__
define __G_MEMORY_OUTPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/goutputstream.inc

define G_TYPE_MEMORY_OUTPUT_STREAM         <g_memory_output_stream_get_type ()>
G_MEMORY_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_MEMORY_OUTPUT_STREAM, GMemoryOutputStream))>
  endm
G_MEMORY_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_MEMORY_OUTPUT_STREAM, GMemoryOutputStreamClass))>
  endm
G_IS_MEMORY_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_MEMORY_OUTPUT_STREAM))>
  endm
G_IS_MEMORY_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_MEMORY_OUTPUT_STREAM))>
  endm
G_MEMORY_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_MEMORY_OUTPUT_STREAM, GMemoryOutputStreamClass))>
  endm


;GMemoryOutputStreamPrivate typedef _GMemoryOutputStreamPrivate

_GMemoryOutputStream    struct
parent_instance         GOutputStream <>
priv                    ptr GMemoryOutputStreamPrivate ?
_GMemoryOutputStream    ends
GMemoryOutputStream     typedef _GMemoryOutputStream

_GMemoryOutputStreamClass struct
parent_class            GOutputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GMemoryOutputStreamClass ends
GMemoryOutputStreamClass typedef _GMemoryOutputStreamClass

CALLBACK(GReallocFunc, :gpointer, :gsize)

g_memory_output_stream_get_type proto

g_memory_output_stream_new proto :gpointer, :gsize, :GReallocFunc, :GDestroyNotify
g_memory_output_stream_new_resizable proto
g_memory_output_stream_get_data proto :ptr
g_memory_output_stream_get_size proto :ptr
g_memory_output_stream_get_data_size proto :ptr
g_memory_output_stream_steal_data proto :ptr

g_memory_output_stream_steal_as_bytes proto :ptr

endif

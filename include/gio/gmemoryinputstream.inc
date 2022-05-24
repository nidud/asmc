ifndef __G_MEMORY_INPUT_STREAM_H__
define __G_MEMORY_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/ginputstream.inc

define G_TYPE_MEMORY_INPUT_STREAM         <g_memory_input_stream_get_type ()>
G_MEMORY_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_MEMORY_INPUT_STREAM, GMemoryInputStream))>
  endm
G_MEMORY_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_MEMORY_INPUT_STREAM, GMemoryInputStreamClass))>
  endm
G_IS_MEMORY_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_MEMORY_INPUT_STREAM))>
  endm
G_IS_MEMORY_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_MEMORY_INPUT_STREAM))>
  endm
G_MEMORY_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_MEMORY_INPUT_STREAM, GMemoryInputStreamClass))>
  endm


;GMemoryInputStreamPrivate typedef _GMemoryInputStreamPrivate

_GMemoryInputStream     struct
parent_instance         GInputStream <>
priv                    ptr GMemoryInputStreamPrivate ?
_GMemoryInputStream     ends
GMemoryInputStream      typedef _GMemoryInputStream

_GMemoryInputStreamClass struct
parent_class            GInputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GMemoryInputStreamClass ends
GMemoryInputStreamClass typedef _GMemoryInputStreamClass


g_memory_input_stream_get_type proto
g_memory_input_stream_new proto
g_memory_input_stream_new_from_data proto :ptr, :gssize, :GDestroyNotify
g_memory_input_stream_new_from_bytes proto :ptr

g_memory_input_stream_add_data proto :ptr, :ptr, :gssize, :GDestroyNotify
g_memory_input_stream_add_bytes proto :ptr, :ptr

endif

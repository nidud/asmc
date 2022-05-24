ifndef __G_SIMPLE_IO_STREAM_H__
define __G_SIMPLE_IO_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc
include gio/giostream.inc

define G_TYPE_SIMPLE_IO_STREAM                  <g_simple_io_stream_get_type ()>
G_SIMPLE_IO_STREAM macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SIMPLE_IO_STREAM, GSimpleIOStream))>
  endm
G_IS_SIMPLE_IO_STREAM macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SIMPLE_IO_STREAM))>
  endm

g_simple_io_stream_get_type proto
g_simple_io_stream_new proto :ptr, :ptr

endif

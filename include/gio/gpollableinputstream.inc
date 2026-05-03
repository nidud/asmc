ifndef __G_POLLABLE_INPUT_STREAM_H__
define __G_POLLABLE_INPUT_STREAM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gio.inc

define G_TYPE_POLLABLE_INPUT_STREAM               <g_pollable_input_stream_get_type ()>
G_POLLABLE_INPUT_STREAM macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_POLLABLE_INPUT_STREAM, GPollableInputStream))>
  endm
G_IS_POLLABLE_INPUT_STREAM macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_POLLABLE_INPUT_STREAM))>
  endm
G_POLLABLE_INPUT_STREAM_GET_INTERFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_POLLABLE_INPUT_STREAM, GPollableInputStreamInterface))>
  endm


GPollableInputStreamInterface struct
g_iface                 GTypeInterface <>
can_poll                proc :ptr
is_readable             proc :ptr
create_source           proc :ptr, :ptr
read_nonblocking        proc :ptr, :ptr, :gsize, :ptr
GPollableInputStreamInterface ends

g_pollable_input_stream_get_type proto
g_pollable_input_stream_can_poll proto :ptr
g_pollable_input_stream_is_readable proto :ptr
g_pollable_input_stream_create_source proto :ptr, :ptr
g_pollable_input_stream_read_nonblocking proto :ptr, :ptr, :gsize, :ptr, :ptr

endif

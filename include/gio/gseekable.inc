ifndef __G_SEEKABLE_H__
define __G_SEEKABLE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SEEKABLE            <g_seekable_get_type ()>
G_SEEKABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SEEKABLE, GSeekable))>
  endm
G_IS_SEEKABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SEEKABLE))>
  endm
G_SEEKABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_SEEKABLE, GSeekableIface))>
  endm

GSeekableIface          struct
g_iface                 GTypeInterface <>
tell                    proc :ptr
can_seek                proc :ptr
seek                    proc :ptr, :goffset, :GSeekType, :ptr, :ptr
can_truncate            proc :ptr
truncate_fn             proc :ptr, :goffset, :ptr, :ptr
GSeekableIface          ends

g_seekable_get_type proto

g_seekable_tell proto :ptr
g_seekable_can_seek proto :ptr
g_seekable_seek proto :ptr, :goffset, :GSeekType, :ptr, :ptr
g_seekable_can_truncate proto :ptr
g_seekable_truncate proto :ptr, :goffset, :ptr, :ptr

endif

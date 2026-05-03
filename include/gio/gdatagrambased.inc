ifndef __G_DATAGRAM_BASED_H__
define __G_DATAGRAM_BASED_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc


define G_TYPE_DATAGRAM_BASED             <g_datagram_based_get_type ()>
G_DATAGRAM_BASED macro inst
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DATAGRAM_BASED, GDatagramBased)>
  endm
G_IS_DATAGRAM_BASED macro inst
  exitm<G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_DATAGRAM_BASED)>
  endm
G_DATAGRAM_BASED_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_DATAGRAM_BASED, GDatagramBasedInterface))>
  endm
G_TYPE_IS_DATAGRAM_BASED macro type
  exitm<(g_type_is_aype), G_TYPE_DATAGRAM_BASED))>
  endm

GDatagramBasedInterface struct
g_iface                 GTypeInterface <>
receive_messages        proc :ptr, :ptr, :guint, :gint, :gint64, :ptr, :ptr
send_messages           proc :ptr, :ptr, :guint, :gint, :gint64, :ptr, :ptr
create_source           proc :ptr, :GIOCondition, :ptr
condition_check         proc :ptr, :GIOCondition
condition_wait          proc :ptr, :GIOCondition, :gint64, :ptr, :ptr
GDatagramBasedInterface ends

g_datagram_based_get_type proto

endif

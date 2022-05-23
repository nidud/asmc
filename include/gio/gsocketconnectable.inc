ifndef __G_SOCKET_CONNECTABLE_H__
define __G_SOCKET_CONNECTABLE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET_CONNECTABLE            <g_socket_connectable_get_type>
G_SOCKET_CONNECTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SOCKET_CONNECTABLE, GSocketConnectable))>
  endm
G_IS_SOCKET_CONNECTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SOCKET_CONNECTABLE))>
  endm
G_SOCKET_CONNECTABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_SOCKET_CONNECTABLE, GSocketConnectableIface))>
  endm


_GSocketConnectableIface struct
g_iface                 GTypeInterface <>
enumerate               proc :ptr
proxy_enumerate         proc :ptr
to_string               proc :ptr
_GSocketConnectableIface ends
GSocketConnectableIface typedef _GSocketConnectableIface

g_socket_connectable_get_type proto
g_socket_connectable_enumerate proto :ptr
g_socket_connectable_proxy_enumerate proto :ptr
g_socket_connectable_to_string proto :ptr

endif

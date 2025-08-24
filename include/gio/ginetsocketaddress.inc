ifndef __G_INET_SOCKET_ADDRESS_H__
define __G_INET_SOCKET_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketaddress.inc

define G_TYPE_INET_SOCKET_ADDRESS         <g_inet_socket_address_get_type ()>
G_INET_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_INET_SOCKET_ADDRESS, GInetSocketAddress))>
  endm
G_INET_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_INET_SOCKET_ADDRESS, GInetSocketAddressClass))>
  endm
G_IS_INET_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_INET_SOCKET_ADDRESS))>
  endm
G_IS_INET_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_INET_SOCKET_ADDRESS))>
  endm
G_INET_SOCKET_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_INET_SOCKET_ADDRESS, GInetSocketAddressClass))>
  endm

GInetSocketAddress      struct
parent_instance         GSocketAddress <>
priv                    ptr GInetSocketAddressPrivate ?
GInetSocketAddress      ends

GInetSocketAddressClass struct
parent_class            GSocketAddressClass <>
GInetSocketAddressClass ends

g_inet_socket_address_get_type proto
g_inet_socket_address_new proto :ptr, :guint16
g_inet_socket_address_new_from_string proto :ptr, :guint
g_inet_socket_address_get_address proto :ptr
g_inet_socket_address_get_port proto :ptr
g_inet_socket_address_get_flowinfo proto :ptr
g_inet_socket_address_get_scope_id proto :ptr

endif

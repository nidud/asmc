ifndef __G_UNIX_SOCKET_ADDRESS_H__
define __G_UNIX_SOCKET_ADDRESS_H__

include gio/gio.inc

define G_TYPE_UNIX_SOCKET_ADDRESS         <g_unix_socket_address_get_type ()>
G_UNIX_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_UNIX_SOCKET_ADDRESS, GUnixSocketAddress))>
  endm
G_UNIX_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_UNIX_SOCKET_ADDRESS, GUnixSocketAddressClass))>
  endm
G_IS_UNIX_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_UNIX_SOCKET_ADDRESS))>
  endm
G_IS_UNIX_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_UNIX_SOCKET_ADDRESS))>
  endm
G_UNIX_SOCKET_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_UNIX_SOCKET_ADDRESS, GUnixSocketAddressClass))>
  endm

GUnixSocketAddress      struct
parent_instance         GSocketAddress <>
priv                    ptr GUnixSocketAddressPrivate ?
GUnixSocketAddress      ends

GUnixSocketAddressClass struct
parent_class            GSocketAddressClass <>
GUnixSocketAddressClass ends
g_unix_socket_address_get_type proto

g_unix_socket_address_new proto :ptr
g_unix_socket_address_new_abstract proto :ptr, :gint
g_unix_socket_address_new_with_type proto :ptr, :gint, :GUnixSocketAddressType
g_unix_socket_address_get_path proto :ptr
g_unix_socket_address_get_path_len proto :ptr
g_unix_socket_address_get_address_type proto :ptr
g_unix_socket_address_get_is_abstract proto :ptr
g_unix_socket_address_abstract_names_supported proto

endif

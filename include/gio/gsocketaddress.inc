ifndef __G_SOCKET_ADDRESS_H__
define __G_SOCKET_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET_ADDRESS         <g_socket_address_get_type ()>
G_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SOCKET_ADDRESS, GSocketAddress))>
  endm
G_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_SOCKET_ADDRESS, GSocketAddressClass))>
  endm
G_IS_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SOCKET_ADDRESS))>
  endm
G_IS_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_SOCKET_ADDRESS))>
  endm
G_SOCKET_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_SOCKET_ADDRESS, GSocketAddressClass))>
  endm

_GSocketAddress         struct
parent_instance         GObject <>
_GSocketAddress         ends
GSocketAddress          typedef _GSocketAddress

_GSocketAddressClass    struct
parent_class            GObjectClass <>
get_family              proc :ptr
get_native_size         proc :ptr
to_native               proc :ptr, :gpointer, :gsize, :ptr
_GSocketAddressClass    ends
GSocketAddressClass     typedef _GSocketAddressClass

g_socket_address_get_type proto
g_socket_address_get_family proto :ptr
g_socket_address_new_from_native proto :gpointer, :gsize
g_socket_address_to_native proto :ptr, :gpointer, :gsize, :ptr
g_socket_address_get_native_size proto :ptr

endif

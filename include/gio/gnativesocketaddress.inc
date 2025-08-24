ifndef __G_NATIVE_SOCKET_ADDRESS_H__
define __G_NATIVE_SOCKET_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketaddress.inc

define G_TYPE_NATIVE_SOCKET_ADDRESS         <g_native_socket_address_get_type ()>
G_NATIVE_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NATIVE_SOCKET_ADDRESS, GNativeSocketAddress))>
  endm
G_NATIVE_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_NATIVE_SOCKET_ADDRESS, GNativeSocketAddressClass))>
  endm
G_IS_NATIVE_SOCKET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NATIVE_SOCKET_ADDRESS))>
  endm
G_IS_NATIVE_SOCKET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_NATIVE_SOCKET_ADDRESS))>
  endm
G_NATIVE_SOCKET_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_NATIVE_SOCKET_ADDRESS, GNativeSocketAddressClass))>
  endm

GNativeSocketAddress    struct
parent_instance         GSocketAddress <>
priv                    ptr GNativeSocketAddressPrivate ?
GNativeSocketAddress    ends

GNativeSocketAddressClass struct
parent_class            GSocketAddressClass <>
GNativeSocketAddressClass ends

g_native_socket_address_get_type proto
g_native_socket_address_new proto :gpointer, :gsize

endif

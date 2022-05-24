ifndef __G_SOCKET_ADDRESS_ENUMERATOR_H__
define __G_SOCKET_ADDRESS_ENUMERATOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET_ADDRESS_ENUMERATOR         <g_socket_address_enumerator_get_type ()>
G_SOCKET_ADDRESS_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SOCKET_ADDRESS_ENUMERATOR, GSocketAddressEnumerator))>
  endm
G_SOCKET_ADDRESS_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_SOCKET_ADDRESS_ENUMERATOR, GSocketAddressEnumeratorClass))>
  endm
G_IS_SOCKET_ADDRESS_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SOCKET_ADDRESS_ENUMERATOR))>
  endm
G_IS_SOCKET_ADDRESS_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_SOCKET_ADDRESS_ENUMERATOR))>
  endm
G_SOCKET_ADDRESS_ENUMERATOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_SOCKET_ADDRESS_ENUMERATOR, GSocketAddressEnumeratorClass))>
  endm


_GSocketAddressEnumerator struct
parent_instance         GObject <>
_GSocketAddressEnumerator ends
GSocketAddressEnumerator typedef _GSocketAddressEnumerator

_GSocketAddressEnumeratorClass struct
parent_class            GObjectClass <>
next                    proc :ptr, :ptr, :ptr
next_async              proc :ptr, :ptr, :GAsyncReadyCallback, :gpointer
next_finish             proc :ptr, :ptr, :ptr
_GSocketAddressEnumeratorClass ends
GSocketAddressEnumeratorClass typedef _GSocketAddressEnumeratorClass

g_socket_address_enumerator_get_type proto
g_socket_address_enumerator_next proto :ptr, :ptr, :ptr
g_socket_address_enumerator_next_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_address_enumerator_next_finish proto :ptr, :ptr, :ptr

endif

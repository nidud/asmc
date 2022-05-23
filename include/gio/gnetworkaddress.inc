ifndef __G_NETWORK_ADDRESS_H__
define __G_NETWORK_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_NETWORK_ADDRESS         <g_network_address_get_type>
G_NETWORK_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NETWORK_ADDRESS, GNetworkAddress))>
  endm
G_NETWORK_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_NETWORK_ADDRESS, GNetworkAddressClass))>
  endm
G_IS_NETWORK_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NETWORK_ADDRESS))>
  endm
G_IS_NETWORK_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_NETWORK_ADDRESS))>
  endm
G_NETWORK_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_NETWORK_ADDRESS, GNetworkAddressClass))>
  endm

;GNetworkAddressPrivate  typedef _GNetworkAddressPrivate

_GNetworkAddress        struct
parent_instance         GObject <>
priv                    ptr GNetworkAddressPrivate ?
_GNetworkAddress        ends
GNetworkAddress         typedef _GNetworkAddress

_GNetworkAddressClass   struct
parent_class            GObjectClass <>
_GNetworkAddressClass   ends
GNetworkAddressClass    typedef _GNetworkAddressClass

g_network_address_get_type proto

g_network_address_new proto :ptr, :guint16
g_network_address_new_loopback proto :guint16
g_network_address_parse proto :ptr, :guint16, :ptr
g_network_address_parse_uri proto :ptr, :guint16, :ptr
g_network_address_get_hostname proto :ptr
g_network_address_get_port proto :ptr
g_network_address_get_scheme proto :ptr

endif

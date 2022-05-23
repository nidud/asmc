ifndef __G_INET_ADDRESS_H__
define __G_INET_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_INET_ADDRESS         <g_inet_address_get_type>
G_INET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_INET_ADDRESS, GInetAddress))>
  endm
G_INET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_INET_ADDRESS, GInetAddressClass))>
  endm
G_IS_INET_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_INET_ADDRESS))>
  endm
G_IS_INET_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_INET_ADDRESS))>
  endm
G_INET_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_INET_ADDRESS, GInetAddressClass))>
  endm

;GInetAddressPrivate     typedef _GInetAddressPrivate

_GInetAddress           struct
parent_instance         GObject <>
priv                    ptr GInetAddressPrivate ?
_GInetAddress           ends
GInetAddress            typedef _GInetAddress

_GInetAddressClass      struct
parent_class            GObjectClass <>
to_string               proc :ptr
to_bytes                proc :ptr
_GInetAddressClass      ends
GInetAddressClass       typedef _GInetAddressClass

g_inet_address_get_type proto
g_inet_address_new_from_string proto :ptr
g_inet_address_new_from_bytes proto :ptr, :GSocketFamily
g_inet_address_new_loopback proto :GSocketFamily
g_inet_address_new_any proto :GSocketFamily
g_inet_address_equal proto :ptr, :ptr
g_inet_address_to_string proto :ptr
g_inet_address_to_bytes proto :ptr
g_inet_address_get_native_size proto :ptr
g_inet_address_get_family proto :ptr
g_inet_address_get_is_any proto :ptr
g_inet_address_get_is_loopback proto :ptr
g_inet_address_get_is_link_local proto :ptr
g_inet_address_get_is_site_local proto :ptr
g_inet_address_get_is_multicast proto :ptr
g_inet_address_get_is_mc_global proto :ptr
g_inet_address_get_is_mc_link_local proto :ptr
g_inet_address_get_is_mc_node_local proto :ptr
g_inet_address_get_is_mc_org_local proto :ptr
g_inet_address_get_is_mc_site_local proto :ptr

endif

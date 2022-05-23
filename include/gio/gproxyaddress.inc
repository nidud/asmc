ifndef __G_PROXY_ADDRESS_H__
define __G_PROXY_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/ginetsocketaddress.inc

define G_TYPE_PROXY_ADDRESS         <g_proxy_address_get_type>
G_PROXY_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_PROXY_ADDRESS, GProxyAddress))>
  endm
G_PROXY_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_PROXY_ADDRESS, GProxyAddressClass))>
  endm
G_IS_PROXY_ADDRESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_PROXY_ADDRESS))>
  endm
G_IS_PROXY_ADDRESS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_PROXY_ADDRESS))>
  endm
G_PROXY_ADDRESS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_PROXY_ADDRESS, GProxyAddressClass))>
  endm

;GProxyAddressPrivate    typedef _GProxyAddressPrivate

_GProxyAddress          struct
parent_instance         GInetSocketAddress <>
priv                    ptr GProxyAddressPrivate ?
_GProxyAddress          ends
GProxyAddress           typedef _GProxyAddress

_GProxyAddressClass     struct
parent_class            GInetSocketAddressClass <>
_GProxyAddressClass     ends
GProxyAddressClass      typedef _GProxyAddressClass


g_proxy_address_get_type proto
g_proxy_address_new proto :ptr, :guint16, :ptr, :ptr, :guint16, :ptr, :ptr
g_proxy_address_get_protocol proto :ptr
g_proxy_address_get_destination_protocol proto :ptr
g_proxy_address_get_destination_hostname proto :ptr
g_proxy_address_get_destination_port proto :ptr
g_proxy_address_get_username proto :ptr
g_proxy_address_get_password proto :ptr
g_proxy_address_get_uri proto :ptr

endif

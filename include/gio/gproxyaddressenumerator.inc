ifndef __G_PROXY_ADDRESS_ENUMERATOR_H__
define __G_PROXY_ADDRESS_ENUMERATOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketaddressenumerator.inc

define G_TYPE_PROXY_ADDRESS_ENUMERATOR         <g_proxy_address_enumerator_get_type ()>
G_PROXY_ADDRESS_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_PROXY_ADDRESS_ENUMERATOR, GProxyAddressEnumerator))>
  endm
G_PROXY_ADDRESS_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_PROXY_ADDRESS_ENUMERATOR, GProxyAddressEnumeratorClass))>
  endm
G_IS_PROXY_ADDRESS_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_PROXY_ADDRESS_ENUMERATOR))>
  endm
G_IS_PROXY_ADDRESS_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_PROXY_ADDRESS_ENUMERATOR))>
  endm
G_PROXY_ADDRESS_ENUMERATOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_PROXY_ADDRESS_ENUMERATOR, GProxyAddressEnumeratorClass))>
  endm

GProxyAddressEnumerator struct
parent_instance         GSocketAddressEnumerator <>
priv                    ptr GProxyAddressEnumeratorPrivate ?
GProxyAddressEnumerator ends

GProxyAddressEnumeratorClass struct
parent_class            GSocketAddressEnumeratorClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
GProxyAddressEnumeratorClass ends

g_proxy_address_enumerator_get_type proto

endif

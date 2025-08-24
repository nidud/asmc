ifndef __G_PROXY_RESOLVER_H__
define __G_PROXY_RESOLVER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_PROXY_RESOLVER         <g_proxy_resolver_get_type ()>
G_PROXY_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_PROXY_RESOLVER, GProxyResolver))>
  endm
G_IS_PROXY_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_PROXY_RESOLVER))>
  endm
G_PROXY_RESOLVER_GET_IFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), G_TYPE_PROXY_RESOLVER, GProxyResolverInterface))>
  endm

define G_PROXY_RESOLVER_EXTENSION_POINT_NAME <"gio-proxy-resolver">

GProxyResolverInterface struct
g_iface                 GTypeInterface <>
is_supported            proc :ptr
lookup                  proc :ptr, :ptr, :ptr, :ptr
lookup_async            proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
lookup_finish           proc :ptr, :ptr, :ptr
GProxyResolverInterface ends

g_proxy_resolver_get_type proto
g_proxy_resolver_get_default proto

g_proxy_resolver_is_supported proto :ptr
g_proxy_resolver_lookup proto :ptr, :ptr, :ptr, :ptr
g_proxy_resolver_lookup_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_proxy_resolver_lookup_finish proto :ptr, :ptr, :ptr

endif

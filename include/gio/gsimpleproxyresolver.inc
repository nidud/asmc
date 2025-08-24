ifndef __G_SIMPLE_PROXY_RESOLVER_H__
define __G_SIMPLE_PROXY_RESOLVER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gproxyresolver.inc

define G_TYPE_SIMPLE_PROXY_RESOLVER         <g_simple_proxy_resolver_get_type ()>
G_SIMPLE_PROXY_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SIMPLE_PROXY_RESOLVER, GSimpleProxyResolver))>
  endm
G_SIMPLE_PROXY_RESOLVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_SIMPLE_PROXY_RESOLVER, GSimpleProxyResolverClass))>
  endm
G_IS_SIMPLE_PROXY_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SIMPLE_PROXY_RESOLVER))>
  endm
G_IS_SIMPLE_PROXY_RESOLVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_SIMPLE_PROXY_RESOLVER))>
  endm
G_SIMPLE_PROXY_RESOLVER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_SIMPLE_PROXY_RESOLVER, GSimpleProxyResolverClass))>
  endm

GSimpleProxyResolver    struct
parent_instance         GObject <>
priv                    ptr GSimpleProxyResolverPrivate ?
GSimpleProxyResolver    ends

GSimpleProxyResolverClass struct
parent_class            GObjectClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
GSimpleProxyResolverClass ends

g_simple_proxy_resolver_get_type proto
g_simple_proxy_resolver_new proto :ptr, :ptr
g_simple_proxy_resolver_set_default_proxy proto :ptr, :ptr
g_simple_proxy_resolver_set_ignore_hosts proto :ptr, :ptr
g_simple_proxy_resolver_set_uri_proxy proto :ptr, :ptr, :ptr

endif

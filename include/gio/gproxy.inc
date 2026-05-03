ifndef __G_PROXY_H__
define __G_PROXY_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_PROXY		<g_proxy_get_type ()>
G_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_PROXY, GProxy))>
  endm
G_IS_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_PROXY))>
  endm
G_PROXY_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_PROXY, GProxyInterface))>
  endm

define G_PROXY_EXTENSION_POINT_NAME <"gio-proxy">

GProxyInterface		struct
g_iface			GTypeInterface <>
connect			proc :ptr, :ptr, :ptr, :ptr, :ptr
connect_async		proc :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
connect_finish		proc :ptr, :ptr, :ptr
supports_hostname	proc :ptr
GProxyInterface		ends

g_proxy_get_type proto
g_proxy_get_default_for_protocol proto :ptr
g_proxy_connect proto :ptr, :ptr, :ptr, :ptr, :ptr
g_proxy_connect_async proto :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_proxy_connect_finish proto :ptr, :ptr, :ptr
g_proxy_supports_hostname proto :ptr

endif

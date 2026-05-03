ifndef __G_SOCKET_CLIENT_H__
define __G_SOCKET_CLIENT_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc


define G_TYPE_SOCKET_CLIENT                                <g_socket_client_get_type ()>
G_SOCKET_CLIENT macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET_CLIENT, GSocketClient))>
  endm
G_SOCKET_CLIENT_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET_CLIENT, GSocketClientClass))>
  endm
G_IS_SOCKET_CLIENT macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET_CLIENT))>
  endm
G_IS_SOCKET_CLIENT_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET_CLIENT))>
  endm
G_SOCKET_CLIENT_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET_CLIENT, GSocketClientClass))>
  endm

GSocketClientClass      struct
parent_class            GObjectClass <>
event                   proc :ptr, :GSocketClientEvent, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
GSocketClientClass      ends

GSocketClient           struct
parent_instance         GObject <>
priv                    ptr GSocketClientPrivate ?
GSocketClient           ends

g_socket_client_get_type proto
g_socket_client_new proto
g_socket_client_get_family proto :ptr
g_socket_client_set_family proto :ptr, :GSocketFamily
g_socket_client_get_socket_type proto :ptr
g_socket_client_set_socket_type proto :ptr, :GSocketType
g_socket_client_get_protocol proto :ptr
g_socket_client_set_protocol proto :ptr, :GSocketProtocol
g_socket_client_get_local_address proto :ptr
g_socket_client_set_local_address proto :ptr, :ptr
g_socket_client_get_timeout proto :ptr
g_socket_client_set_timeout proto :ptr, :guint
g_socket_client_get_enable_proxy proto :ptr
g_socket_client_set_enable_proxy proto :ptr, :gboolean

g_socket_client_get_tls proto :ptr
g_socket_client_set_tls proto :ptr, :gboolean
g_socket_client_get_tls_validation_flags proto :ptr
g_socket_client_set_tls_validation_flags proto :ptr, :GTlsCertificateFlags
g_socket_client_get_proxy_resolver proto :ptr
g_socket_client_set_proxy_resolver proto :ptr, :ptr

g_socket_client_connect proto :ptr, :ptr, :ptr, :ptr
g_socket_client_connect_to_host proto :ptr, :ptr, :guint16, :ptr, :ptr
g_socket_client_connect_to_service proto :ptr, :ptr, :ptr, :ptr, :ptr
g_socket_client_connect_to_uri proto :ptr, :ptr, :guint16, :ptr, :ptr
g_socket_client_connect_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_client_connect_finish proto :ptr, :ptr, :ptr
g_socket_client_connect_to_host_async proto :ptr, :ptr, :guint16, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_client_connect_to_host_finish proto :ptr, :ptr, :ptr

g_socket_client_connect_to_service_async proto :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_client_connect_to_service_finish proto :ptr, :ptr, :ptr
g_socket_client_connect_to_uri_async proto :ptr, :ptr, :guint16, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_client_connect_to_uri_finish proto :ptr, :ptr, :ptr
g_socket_client_add_application_proxy proto :ptr, :ptr

endif

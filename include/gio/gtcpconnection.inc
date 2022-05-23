ifndef __G_TCP_CONNECTION_H__
define __G_TCP_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketconnection.inc

define G_TYPE_TCP_CONNECTION                               <g_tcp_connection_get_type>
G_TCP_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TCP_CONNECTION, GTcpConnection))>
  endm
G_TCP_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TCP_CONNECTION, GTcpConnectionClass))>
  endm
G_IS_TCP_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TCP_CONNECTION))>
  endm
G_IS_TCP_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TCP_CONNECTION))>
  endm
G_TCP_CONNECTION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TCP_CONNECTION, GTcpConnectionClass))>
  endm

;GTcpConnectionPrivate   typedef _GTcpConnectionPrivate

_GTcpConnectionClass    struct
parent_class            GSocketConnectionClass <>
_GTcpConnectionClass    ends
GTcpConnectionClass     typedef _GTcpConnectionClass

_GTcpConnection         struct
parent_instance         GSocketConnection <>
priv                    ptr GTcpConnectionPrivate ?
_GTcpConnection         ends
GTcpConnection          typedef _GTcpConnection

g_tcp_connection_get_type proto
g_tcp_connection_set_graceful_disconnect proto :ptr, :gboolean
g_tcp_connection_get_graceful_disconnect proto :ptr

endif

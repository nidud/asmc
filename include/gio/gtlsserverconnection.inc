ifndef __G_TLS_SERVER_CONNECTION_H__
define __G_TLS_SERVER_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gtlsconnection.inc

define G_TYPE_TLS_SERVER_CONNECTION                <g_tls_server_connection_get_type ()>
G_TLS_SERVER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_SERVER_CONNECTION, GTlsServerConnection))>
  endm
G_IS_TLS_SERVER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_SERVER_CONNECTION))>
  endm
G_TLS_SERVER_CONNECTION_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_TLS_SERVER_CONNECTION, GTlsServerConnectionInterface))>
  endm

_GTlsServerConnectionInterface struct
g_iface                 GTypeInterface <>
_GTlsServerConnectionInterface ends
GTlsServerConnectionInterface typedef _GTlsServerConnectionInterface

g_tls_server_connection_get_type proto
g_tls_server_connection_new proto :ptr, :ptr, :ptr

endif

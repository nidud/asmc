ifndef __G_DTLS_SERVER_CONNECTION_H__
define __G_DTLS_SERVER_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gdtlsconnection.inc

define G_TYPE_DTLS_SERVER_CONNECTION                <g_dtls_server_connection_get_type>
G_DTLS_SERVER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DTLS_SERVER_CONNECTION, GDtlsServerConnection))>
  endm
G_IS_DTLS_SERVER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_DTLS_SERVER_CONNECTION))>
  endm
G_DTLS_SERVER_CONNECTION_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_DTLS_SERVER_CONNECTION, GDtlsServerConnectionInterface))>
  endm


_GDtlsServerConnectionInterface struct
g_iface                 GTypeInterface <>
_GDtlsServerConnectionInterface ends
GDtlsServerConnectionInterface typedef _GDtlsServerConnectionInterface

g_dtls_server_connection_get_type proto
g_dtls_server_connection_new proto :ptr, :ptr, :ptr

endif

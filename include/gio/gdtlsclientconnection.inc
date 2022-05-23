ifndef __G_DTLS_CLIENT_CONNECTION_H__
define __G_DTLS_CLIENT_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gdtlsconnection.inc

define G_TYPE_DTLS_CLIENT_CONNECTION                <g_dtls_client_connection_get_type>
G_DTLS_CLIENT_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DTLS_CLIENT_CONNECTION, GDtlsClientConnection))>
  endm
G_IS_DTLS_CLIENT_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_DTLS_CLIENT_CONNECTION))>
  endm
G_DTLS_CLIENT_CONNECTION_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_DTLS_CLIENT_CONNECTION, GDtlsClientConnectionInterface))>
  endm

_GDtlsClientConnectionInterface struct
g_iface                 GTypeInterface <>
_GDtlsClientConnectionInterface ends
GDtlsClientConnectionInterface typedef _GDtlsClientConnectionInterface

g_dtls_client_connection_get_type proto
g_dtls_client_connection_new proto :ptr, :ptr, :ptr
g_dtls_client_connection_get_validation_flags proto :ptr
g_dtls_client_connection_set_validation_flags proto :ptr, :GTlsCertificateFlags
g_dtls_client_connection_get_server_identity proto :ptr
g_dtls_client_connection_set_server_identity proto :ptr, :ptr
g_dtls_client_connection_get_accepted_cas proto :ptr

endif

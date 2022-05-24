ifndef __G_TLS_CLIENT_CONNECTION_H__
define __G_TLS_CLIENT_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gtlsconnection.inc

define G_TYPE_TLS_CLIENT_CONNECTION                <g_tls_client_connection_get_type ()>
G_TLS_CLIENT_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_CLIENT_CONNECTION, GTlsClientConnection))>
  endm
G_IS_TLS_CLIENT_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_CLIENT_CONNECTION))>
  endm
G_TLS_CLIENT_CONNECTION_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_TLS_CLIENT_CONNECTION, GTlsClientConnectionInterface))>
  endm

_GTlsClientConnectionInterface struct
g_iface                 GTypeInterface <>
copy_session_state      proc :ptr, :ptr
_GTlsClientConnectionInterface ends
GTlsClientConnectionInterface typedef _GTlsClientConnectionInterface

g_tls_client_connection_get_type proto
g_tls_client_connection_new proto :ptr, :ptr, :ptr
g_tls_client_connection_get_validation_flags proto :ptr
g_tls_client_connection_set_validation_flags proto :ptr, :GTlsCertificateFlags
g_tls_client_connection_get_server_identity proto :ptr
g_tls_client_connection_set_server_identity proto :ptr, :ptr
g_tls_client_connection_get_use_ssl3 proto :ptr
g_tls_client_connection_set_use_ssl3 proto :ptr, :gboolean
g_tls_client_connection_get_accepted_cas proto :ptr
g_tls_client_connection_copy_session_state proto :ptr, :ptr

endif

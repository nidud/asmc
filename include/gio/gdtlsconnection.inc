ifndef __G_DTLS_CONNECTION_H__
define __G_DTLS_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gdatagrambased.inc

define G_TYPE_DTLS_CONNECTION                <g_dtls_connection_get_type>
G_DTLS_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DTLS_CONNECTION, GDtlsConnection))>
  endm
G_IS_DTLS_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_DTLS_CONNECTION))>
  endm
G_DTLS_CONNECTION_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_DTLS_CONNECTION, GDtlsConnectionInterface))>
  endm

_GDtlsConnectionInterface struct
g_iface                 GTypeInterface <>
accept_certificate      proc :ptr, :ptr, :GTlsCertificateFlags
handshake               proc :ptr, :ptr, :ptr
handshake_async         proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
handshake_finish        proc :ptr, :ptr, :ptr
shutdown                proc :ptr, :gboolean, :gboolean, :ptr, :ptr
shutdown_async          proc :ptr, :gboolean, :gboolean, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
shutdown_finish         proc :ptr, :ptr, :ptr
set_advertised_protocols proc :ptr, :ptr
get_negotiated_protocol proc :ptr
get_binding_data        proc :ptr, :GTlsChannelBindingType, :ptr, :ptr
_GDtlsConnectionInterface ends
GDtlsConnectionInterface typedef _GDtlsConnectionInterface

g_dtls_connection_get_type proto
g_dtls_connection_set_database proto :ptr, :ptr
g_dtls_connection_get_database proto :ptr
g_dtls_connection_set_certificate proto :ptr, :ptr
g_dtls_connection_get_certificate proto :ptr
g_dtls_connection_set_interaction proto :ptr, :ptr
g_dtls_connection_get_interaction proto :ptr
g_dtls_connection_get_peer_certificate proto :ptr
g_dtls_connection_get_peer_certificate_errors proto :ptr
g_dtls_connection_set_require_close_notify proto :ptr, :gboolean
g_dtls_connection_get_require_close_notify proto :ptr
g_dtls_connection_set_rehandshake_mode proto :ptr, :GTlsRehandshakeMode
g_dtls_connection_get_rehandshake_mode proto :ptr
g_dtls_connection_handshake proto :ptr, :ptr, :ptr
g_dtls_connection_handshake_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_dtls_connection_handshake_finish proto :ptr, :ptr, :ptr
g_dtls_connection_shutdown proto :ptr, :gboolean, :gboolean, :ptr, :ptr
g_dtls_connection_shutdown_async proto :ptr, :gboolean, :gboolean, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_dtls_connection_shutdown_finish proto :ptr, :ptr, :ptr
g_dtls_connection_close proto :ptr, :ptr, :ptr
g_dtls_connection_close_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_dtls_connection_close_finish proto :ptr, :ptr, :ptr
g_dtls_connection_emit_accept_certificate proto :ptr, :ptr, :GTlsCertificateFlags
g_dtls_connection_set_advertised_protocols proto :ptr, :ptr
g_dtls_connection_get_negotiated_protocol proto :ptr
g_dtls_connection_get_channel_binding_data proto :ptr, :GTlsChannelBindingType, :ptr, :ptr
g_dtls_connection_get_protocol_version proto :ptr
g_dtls_connection_get_ciphersuite_name proto :ptr

endif

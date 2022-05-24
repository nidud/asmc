ifndef __G_TLS_CONNECTION_H__
define __G_TLS_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giostream.inc

define G_TYPE_TLS_CONNECTION            <g_tls_connection_get_type ()>
G_TLS_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_CONNECTION, GTlsConnection))>
  endm
G_TLS_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_CONNECTION, GTlsConnectionClass))>
  endm
G_IS_TLS_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_CONNECTION))>
  endm
G_IS_TLS_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_CONNECTION))>
  endm
G_TLS_CONNECTION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_CONNECTION, GTlsConnectionClass))>
  endm

;GTlsConnectionPrivate   typedef _GTlsConnectionPrivate

_GTlsConnection         struct
parent_instance         GIOStream <>
priv                    ptr GTlsConnectionPrivate ?
_GTlsConnection         ends
GTlsConnection          typedef _GTlsConnection

_GTlsConnectionClass    struct
parent_class            GIOStreamClass <>
accept_certificate      proc :ptr, :ptr, :GTlsCertificateFlags
handshake               proc :ptr, :ptr, :ptr
handshake_async         proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
handshake_finish        proc :ptr, :ptr, :ptr
get_binding_data        proc :ptr, :GTlsChannelBindingType, :ptr, :ptr
get_negotiated_protocol proc :ptr
padding                 gpointer 6 dup(?)
_GTlsConnectionClass    ends
GTlsConnectionClass     typedef _GTlsConnectionClass

g_tls_connection_get_type proto
g_tls_connection_set_use_system_certdb proto :ptr, :gboolean
g_tls_connection_get_use_system_certdb proto :ptr
g_tls_connection_set_database proto :ptr, :ptr
g_tls_connection_get_database proto :ptr
g_tls_connection_set_certificate proto :ptr, :ptr
g_tls_connection_get_certificate proto :ptr
g_tls_connection_set_interaction proto :ptr, :ptr
g_tls_connection_get_interaction proto :ptr
g_tls_connection_get_peer_certificate proto :ptr
g_tls_connection_get_peer_certificate_errors proto :ptr
g_tls_connection_set_require_close_notify proto :ptr, :gboolean
g_tls_connection_get_require_close_notify proto :ptr
g_tls_connection_set_rehandshake_mode proto :ptr, :GTlsRehandshakeMode
g_tls_connection_get_rehandshake_mode proto :ptr

g_tls_connection_set_advertised_protocols proto :ptr, :ptr
g_tls_connection_get_negotiated_protocol proto :ptr
g_tls_connection_get_channel_binding_data proto :ptr, :GTlsChannelBindingType, :ptr, :ptr
g_tls_connection_handshake proto :ptr, :ptr, :ptr
g_tls_connection_handshake_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_connection_handshake_finish proto :ptr, :ptr, :ptr
g_tls_connection_get_protocol_version proto :ptr
g_tls_connection_get_ciphersuite_name proto :ptr

define G_TLS_ERROR <g_tls_error_quark ()>
g_tls_error_quark proto

define G_TLS_CHANNEL_BINDING_ERROR <g_tls_channel_binding_error_quark ()>
g_tls_channel_binding_error_quark proto
g_tls_connection_emit_accept_certificate proto :ptr, :ptr, :GTlsCertificateFlags

endif

ifndef __G_TLS_BACKEND_H__
define __G_TLS_BACKEND_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TLS_BACKEND_EXTENSION_POINT_NAME <"gio-tls-backend">

define G_TYPE_TLS_BACKEND               <g_tls_backend_get_type ()>
G_TLS_BACKEND macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_TLS_BACKEND, GTlsBackend))>
  endm
G_IS_TLS_BACKEND macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_TLS_BACKEND))>
  endm
G_TLS_BACKEND_GET_INTERFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_TLS_BACKEND, GTlsBackendInterface))>
  endm

;GTlsBackend             typedef _GTlsBackend

_GTlsBackendInterface   struct
g_iface                 GTypeInterface <>
supports_tls            proc :ptr
get_certificate_type    proc
get_client_connection_type proc
get_server_connection_type proc
get_file_database_type  proc
get_default_database    proc :ptr
supports_dtls           proc :ptr
get_dtls_client_connection_type proc
get_dtls_server_connection_type proc
_GTlsBackendInterface   ends
GTlsBackendInterface    typedef _GTlsBackendInterface

g_tls_backend_get_type proto
g_tls_backend_get_default proto
g_tls_backend_get_default_database proto :ptr
g_tls_backend_set_default_database proto :ptr, :ptr
g_tls_backend_supports_tls proto :ptr
g_tls_backend_supports_dtls proto :ptr
g_tls_backend_get_certificate_type proto :ptr
g_tls_backend_get_client_connection_type proto :ptr
g_tls_backend_get_server_connection_type proto :ptr
g_tls_backend_get_file_database_type proto :ptr
g_tls_backend_get_dtls_client_connection_type proto :ptr
g_tls_backend_get_dtls_server_connection_type proto :ptr

endif

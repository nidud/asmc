ifndef __G_TLS_DATABASE_H__
define __G_TLS_DATABASE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TLS_DATABASE_PURPOSE_AUTHENTICATE_SERVER <"1.3.6.1.5.5.7.3.1">
define G_TLS_DATABASE_PURPOSE_AUTHENTICATE_CLIENT <"1.3.6.1.5.5.7.3.2">

define G_TYPE_TLS_DATABASE            <g_tls_database_get_type ()>
G_TLS_DATABASE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_DATABASE, GTlsDatabase))>
  endm
G_TLS_DATABASE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_DATABASE, GTlsDatabaseClass))>
  endm
G_IS_TLS_DATABASE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_DATABASE))>
  endm
G_IS_TLS_DATABASE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_DATABASE))>
  endm
G_TLS_DATABASE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_DATABASE, GTlsDatabaseClass))>
  endm

GTlsDatabase            struct
parent_instance         GObject <>
priv                    ptr GTlsDatabasePrivate ?
GTlsDatabase            ends

GTlsDatabaseClass       struct
parent_class            GObjectClass <>
verify_chain            proc :ptr, :ptr, :ptr, :ptr, :ptr, :GTlsDatabaseVerifyFlags, :ptr, :ptr
verify_chain_async      proc :ptr, :ptr, :ptr, :ptr, :ptr, :GTlsDatabaseVerifyFlags, :ptr, :GAsyncReadyCallback, :gpointer
verify_chain_finish     proc :ptr, :ptr, :ptr
create_certificate_handle proc :ptr, :ptr
lookup_certificate_for_handle proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
lookup_certificate_for_handle_async proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
lookup_certificate_for_handle_finish proc :ptr, :ptr, :ptr
lookup_certificate_issuer proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
lookup_certificate_issuer_async proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
lookup_certificate_issuer_finish proc :ptr, :ptr, :ptr
lookup_certificates_issued_by proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
lookup_certificates_issued_by_async proc :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
lookup_certificates_issued_by_finish proc :ptr, :ptr, :ptr
padding                 gpointer 16 dup(?)
GTlsDatabaseClass       ends

g_tls_database_get_type proto
g_tls_database_verify_chain proto :ptr, :ptr, :ptr, :ptr, :ptr, :GTlsDatabaseVerifyFlags, :ptr, :ptr
g_tls_database_verify_chain_async proto :ptr, :ptr, :ptr, :ptr, :ptr, :GTlsDatabaseVerifyFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_database_verify_chain_finish proto :ptr, :ptr, :ptr
g_tls_database_create_certificate_handle proto :ptr, :ptr
g_tls_database_lookup_certificate_for_handle proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
g_tls_database_lookup_certificate_for_handle_async proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_database_lookup_certificate_for_handle_finish proto :ptr, :ptr, :ptr
g_tls_database_lookup_certificate_issuer proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
g_tls_database_lookup_certificate_issuer_async proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_database_lookup_certificate_issuer_finish proto :ptr, :ptr, :ptr
g_tls_database_lookup_certificates_issued_by proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :ptr
g_tls_database_lookup_certificates_issued_by_async proto :ptr, :ptr, :ptr, :GTlsDatabaseLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_database_lookup_certificates_issued_by_finish proto :ptr, :ptr, :ptr

endif

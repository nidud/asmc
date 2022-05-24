ifndef __G_TLS_CERTIFICATE_H__
define __G_TLS_CERTIFICATE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TLS_CERTIFICATE            <g_tls_certificate_get_type ()>
G_TLS_CERTIFICATE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_CERTIFICATE, GTlsCertificate))>
  endm
G_TLS_CERTIFICATE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TLS_CERTIFICATE, GTlsCertificateClass))>
  endm
G_IS_TLS_CERTIFICATE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_CERTIFICATE))>
  endm
G_IS_TLS_CERTIFICATE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TLS_CERTIFICATE))>
  endm
G_TLS_CERTIFICATE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TLS_CERTIFICATE, GTlsCertificateClass))>
  endm

;GTlsCertificatePrivate  typedef _GTlsCertificatePrivate

_GTlsCertificate        struct
parent_instance         GObject <>
priv                    ptr GTlsCertificatePrivate ?
_GTlsCertificate        ends
GTlsCertificate         typedef _GTlsCertificate

_GTlsCertificateClass   struct
parent_class            GObjectClass <>
verify                  proc :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
_GTlsCertificateClass   ends
GTlsCertificateClass    typedef _GTlsCertificateClass

g_tls_certificate_get_type proto
g_tls_certificate_new_from_pem proto :ptr, :gssize, :ptr
g_tls_certificate_new_from_pkcs12 proto :ptr, :gsize, :ptr, :ptr
g_tls_certificate_new_from_file_with_password proto :ptr, :ptr, :ptr
g_tls_certificate_new_from_file proto :ptr, :ptr
g_tls_certificate_new_from_files proto :ptr, :ptr, :ptr
g_tls_certificate_new_from_pkcs11_uris proto :ptr, :ptr, :ptr
g_tls_certificate_list_new_from_file proto :ptr, :ptr
g_tls_certificate_get_issuer proto :ptr
g_tls_certificate_verify proto :ptr, :ptr, :ptr
g_tls_certificate_is_same proto :ptr, :ptr
g_tls_certificate_get_not_valid_before proto :ptr
g_tls_certificate_get_not_valid_after proto :ptr
g_tls_certificate_get_subject_name proto :ptr
g_tls_certificate_get_issuer_name proto :ptr
g_tls_certificate_get_dns_names proto :ptr
g_tls_certificate_get_ip_addresses proto :ptr

endif

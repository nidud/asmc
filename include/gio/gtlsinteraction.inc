ifndef __G_TLS_INTERACTION_H__
define __G_TLS_INTERACTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TLS_INTERACTION         <g_tls_interaction_get_type ()>
G_TLS_INTERACTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_TLS_INTERACTION, GTlsInteraction))>
  endm
G_TLS_INTERACTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_TLS_INTERACTION, GTlsInteractionClass))>
  endm
G_IS_TLS_INTERACTION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_TLS_INTERACTION))>
  endm
G_IS_TLS_INTERACTION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_TLS_INTERACTION))>
  endm
G_TLS_INTERACTION_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_TLS_INTERACTION, GTlsInteractionClass))>
  endm

;GTlsInteractionPrivate  typedef _GTlsInteractionPrivate

_GTlsInteraction        struct
parent_instance         GObject <>
priv                    ptr GTlsInteractionPrivate ?
_GTlsInteraction        ends
GTlsInteraction         typedef _GTlsInteraction

_GTlsInteractionClass   struct
parent_class            GObjectClass <>
ask_password            proc :ptr, :ptr, :ptr, :ptr
ask_password_async      proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
ask_password_finish     proc :ptr, :ptr, :ptr
request_certificate     proc :ptr, :ptr, :GTlsCertificateRequestFlags, :ptr, :ptr
request_certificate_async proc :ptr, :ptr, :GTlsCertificateRequestFlags, :ptr, :GAsyncReadyCallback, :gpointer
request_certificate_finish proc :ptr, :ptr, :ptr
padding                 gpointer 21 dup(?)
_GTlsInteractionClass   ends
GTlsInteractionClass    typedef _GTlsInteractionClass

g_tls_interaction_get_type proto
g_tls_interaction_invoke_ask_password proto :ptr, :ptr, :ptr, :ptr
g_tls_interaction_ask_password proto :ptr, :ptr, :ptr, :ptr
g_tls_interaction_ask_password_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_interaction_ask_password_finish proto :ptr, :ptr, :ptr
g_tls_interaction_invoke_request_certificate proto :ptr, :ptr, :GTlsCertificateRequestFlags, :ptr, :ptr
g_tls_interaction_request_certificate proto :ptr, :ptr, :GTlsCertificateRequestFlags, :ptr, :ptr
g_tls_interaction_request_certificate_async proto :ptr, :ptr, :GTlsCertificateRequestFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_tls_interaction_request_certificate_finish proto :ptr, :ptr, :ptr

endif

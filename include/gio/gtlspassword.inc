ifndef __G_TLS_PASSWORD_H__
define __G_TLS_PASSWORD_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TLS_PASSWORD         <g_tls_password_get_type ()>
G_TLS_PASSWORD macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_TLS_PASSWORD, GTlsPassword))>
  endm
G_TLS_PASSWORD_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_TLS_PASSWORD, GTlsPasswordClass))>
  endm
G_IS_TLS_PASSWORD macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_TLS_PASSWORD))>
  endm
G_IS_TLS_PASSWORD_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_TLS_PASSWORD))>
  endm
G_TLS_PASSWORD_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_TLS_PASSWORD, GTlsPasswordClass))>
  endm

;GTlsPasswordPrivate     typedef _GTlsPasswordPrivate

_GTlsPassword           struct
parent_instance         GObject <>
priv                    ptr GTlsPasswordPrivate ?
_GTlsPassword           ends

_GTlsPasswordClass      struct
parent_class            GObjectClass <>
get_value               proc :ptr, :ptr
set_value               proc :ptr, :ptr, :gssize, :GDestroyNotify
get_default_warning     proc :ptr
padding                 gpointer 4 dup(?)
_GTlsPasswordClass      ends
GTlsPasswordClass       typedef _GTlsPasswordClass

g_tls_password_get_type proto
g_tls_password_new proto :GTlsPasswordFlags, :ptr
g_tls_password_get_value proto :ptr, :ptr
g_tls_password_set_value proto :ptr, :ptr, :gssize
g_tls_password_set_value_full proto :ptr, :ptr, :gssize, :GDestroyNotify
g_tls_password_get_flags proto :ptr
g_tls_password_set_flags proto :ptr, :GTlsPasswordFlags
g_tls_password_get_description proto :ptr
g_tls_password_set_description proto :ptr, :ptr
g_tls_password_get_warning proto :ptr
g_tls_password_set_warning proto :ptr, :ptr

endif

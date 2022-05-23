ifndef __G_CREDENTIALS_H__
define __G_CREDENTIALS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

ifdef G_OS_UNIX

include unistd.inc
include sys/types.inc
endif

define G_TYPE_CREDENTIALS         <g_credentials_get_type>
G_CREDENTIALS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_CREDENTIALS, GCredentials))>
  endm
G_CREDENTIALS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_CREDENTIALS, GCredentialsClass))>
  endm
G_CREDENTIALS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_CREDENTIALS, GCredentialsClass))>
  endm
G_IS_CREDENTIALS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_CREDENTIALS))>
  endm
G_IS_CREDENTIALS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_CREDENTIALS))>
  endm

;GCredentialsClass       typedef _GCredentialsClass

g_credentials_get_type proto
g_credentials_new proto
g_credentials_to_string proto :ptr
g_credentials_get_native proto :ptr, :GCredentialsType
g_credentials_set_native proto :ptr, :GCredentialsType, :gpointer
g_credentials_is_same_user proto :ptr, :ptr, :ptr

ifdef G_OS_UNIX
g_credentials_get_unix_pid proto :ptr, :ptr
g_credentials_get_unix_user proto :ptr, :ptr
g_credentials_set_unix_user proto :ptr, :uid_t, :ptr
endif

endif

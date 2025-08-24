ifndef __G_UNIX_CREDENTIALS_MESSAGE_H__
define __G_UNIX_CREDENTIALS_MESSAGE_H__

include gio/gio.inc

define G_TYPE_UNIX_CREDENTIALS_MESSAGE         <g_unix_credentials_message_get_type ()>
G_UNIX_CREDENTIALS_MESSAGE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_UNIX_CREDENTIALS_MESSAGE, GUnixCredentialsMessage))>
  endm
G_UNIX_CREDENTIALS_MESSAGE_CLASS macro c
  exitm<(G_TYPE_CHECK_CLASS_CAST ((c), G_TYPE_UNIX_CREDENTIALS_MESSAGE, GUnixCredentialsMessageClass))>
  endm
G_IS_UNIX_CREDENTIALS_MESSAGE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_UNIX_CREDENTIALS_MESSAGE))>
  endm
G_IS_UNIX_CREDENTIALS_MESSAGE_CLASS macro c
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((c), G_TYPE_UNIX_CREDENTIALS_MESSAGE))>
  endm
G_UNIX_CREDENTIALS_MESSAGE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_UNIX_CREDENTIALS_MESSAGE, GUnixCredentialsMessageClass))>
  endm

GUnixCredentialsMessageClass struct
parent_class            GSocketControlMessageClass <>
_g_reserved1            proc
_g_reserved2            proc
GUnixCredentialsMessageClass ends

GUnixCredentialsMessage struct
parent_instance         GSocketControlMessage <>
priv                    ptr GUnixCredentialsMessagePrivate ?
GUnixCredentialsMessage ends

g_unix_credentials_message_get_type proto
g_unix_credentials_message_new proto
g_unix_credentials_message_new_with_credentials proto :ptr
g_unix_credentials_message_get_credentials proto :ptr
g_unix_credentials_message_is_supported proto

endif

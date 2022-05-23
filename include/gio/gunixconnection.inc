ifndef __G_UNIX_CONNECTION_H__
define __G_UNIX_CONNECTION_H__

include gio/gio.inc

define G_TYPE_UNIX_CONNECTION                              <g_unix_connection_get_type>
G_UNIX_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_UNIX_CONNECTION, GUnixConnection))>
  endm
G_UNIX_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_UNIX_CONNECTION, GUnixConnectionClass))>
  endm
G_IS_UNIX_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_UNIX_CONNECTION))>
  endm
G_IS_UNIX_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_UNIX_CONNECTION))>
  endm
G_UNIX_CONNECTION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_UNIX_CONNECTION, GUnixConnectionClass))>
  endm

;GUnixConnectionPrivate  typedef _GUnixConnectionPrivate

_GUnixConnectionClass   struct
parent_class            GSocketConnectionClass <>
_GUnixConnectionClass   ends
GUnixConnectionClass    typedef _GUnixConnectionClass

_GUnixConnection        struct
parent_instance         GSocketConnection <>
priv                    ptr GUnixConnectionPrivate ?
_GUnixConnection        ends
GUnixConnection         typedef _GUnixConnection

g_unix_connection_get_type proto
g_unix_connection_send_fd proto :ptr, :gint, :ptr, :ptr
g_unix_connection_receive_fd proto :ptr, :ptr, :ptr
g_unix_connection_send_credentials proto :ptr, :ptr, :ptr
g_unix_connection_send_credentials_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_unix_connection_send_credentials_finish proto :ptr, :ptr, :ptr
g_unix_connection_receive_credentials proto :ptr, :ptr, :ptr
g_unix_connection_receive_credentials_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_unix_connection_receive_credentials_finish proto :ptr, :ptr, :ptr

endif

ifndef __G_SOCKET_CONNECTION_H__
define __G_SOCKET_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include glib-object.inc
include gio/gsocket.inc
include gio/giostream.inc

define G_TYPE_SOCKET_CONNECTION                            <g_socket_connection_get_type>
G_SOCKET_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET_CONNECTION, GSocketConnection))>
  endm
G_SOCKET_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET_CONNECTION, GSocketConnectionClass))>
  endm
G_IS_SOCKET_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET_CONNECTION))>
  endm
G_IS_SOCKET_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET_CONNECTION))>
  endm
G_SOCKET_CONNECTION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET_CONNECTION, GSocketConnectionClass))>
  endm

;GSocketConnectionPrivate typedef _GSocketConnectionPrivate

_GSocketConnectionClass struct
parent_class            GIOStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_GSocketConnectionClass ends
GSocketConnectionClass  typedef _GSocketConnectionClass

_GSocketConnection      struct
parent_instance         GIOStream <>
priv                    ptr GSocketConnectionPrivate ?
_GSocketConnection      ends
GSocketConnection       typedef _GSocketConnection

g_socket_connection_get_type proto

g_socket_connection_is_connected proto :ptr
g_socket_connection_connect proto :ptr, :ptr, :ptr, :ptr
g_socket_connection_connect_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_connection_connect_finish proto :ptr, :ptr, :ptr

g_socket_connection_get_socket proto :ptr
g_socket_connection_get_local_address proto :ptr, :ptr
g_socket_connection_get_remote_address proto :ptr, :ptr

g_socket_connection_factory_register_type proto :GType, :GSocketFamily, :GSocketType, :gint
g_socket_connection_factory_lookup_type proto :GSocketFamily, :GSocketType, :gint
g_socket_connection_factory_create_connection proto :ptr

endif

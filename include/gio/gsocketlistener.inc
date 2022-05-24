ifndef __G_SOCKET_LISTENER_H__
define __G_SOCKET_LISTENER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET_LISTENER                              <g_socket_listener_get_type ()>
G_SOCKET_LISTENER macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET_LISTENER, GSocketListener))>
  endm
G_SOCKET_LISTENER_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET_LISTENER, GSocketListenerClass))>
  endm
G_IS_SOCKET_LISTENER macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET_LISTENER))>
  endm
G_IS_SOCKET_LISTENER_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET_LISTENER))>
  endm
G_SOCKET_LISTENER_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET_LISTENER, GSocketListenerClass))>
  endm

;GSocketListenerPrivate  typedef _GSocketListenerPrivate

_GSocketListenerClass   struct
parent_class            GObjectClass <>
changed                 proc :ptr
event                   proc :ptr, :GSocketListenerEvent, :ptr
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_GSocketListenerClass   ends
GSocketListenerClass    typedef _GSocketListenerClass

_GSocketListener        struct
parent_instance         GObject <>
priv                    ptr GSocketListenerPrivate ?
_GSocketListener        ends
GSocketListener         typedef _GSocketListener

g_socket_listener_get_type proto
g_socket_listener_new proto
g_socket_listener_set_backlog proto :ptr, :sdword

g_socket_listener_add_socket proto :ptr, :ptr, :ptr, :ptr
g_socket_listener_add_address proto :ptr, :ptr, :GSocketType, :GSocketProtocol, :ptr, :ptr, :ptr
g_socket_listener_add_inet_port proto :ptr, :guint16, :ptr, :ptr
g_socket_listener_add_any_inet_port proto :ptr, :ptr, :ptr

g_socket_listener_accept_socket proto :ptr, :ptr, :ptr, :ptr
g_socket_listener_accept_socket_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_listener_accept_socket_finish proto :ptr, :ptr, :ptr, :ptr

g_socket_listener_accept proto :ptr, :ptr, :ptr, :ptr
g_socket_listener_accept_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_socket_listener_accept_finish proto :ptr, :ptr, :ptr, :ptr
g_socket_listener_close proto :ptr

endif

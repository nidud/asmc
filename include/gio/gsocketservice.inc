ifndef __G_SOCKET_SERVICE_H__
define __G_SOCKET_SERVICE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketlistener.inc

define G_TYPE_SOCKET_SERVICE                               <g_socket_service_get_type ()>
G_SOCKET_SERVICE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET_SERVICE, GSocketService))>
  endm
G_SOCKET_SERVICE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET_SERVICE, GSocketServiceClass))>
  endm
G_IS_SOCKET_SERVICE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET_SERVICE))>
  endm
G_IS_SOCKET_SERVICE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET_SERVICE))>
  endm
G_SOCKET_SERVICE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET_SERVICE, GSocketServiceClass))>
  endm

;GSocketServicePrivate   typedef _GSocketServicePrivate

_GSocketServiceClass    struct
parent_class            GSocketListenerClass <>
incoming                proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_GSocketServiceClass    ends
GSocketServiceClass     typedef _GSocketServiceClass

_GSocketService         struct
parent_instance         GSocketListener <>
priv                    ptr GSocketServicePrivate ?
_GSocketService         ends
GSocketService          typedef _GSocketService

g_socket_service_get_type proto
g_socket_service_new proto
g_socket_service_start proto :ptr
g_socket_service_stop proto :ptr
g_socket_service_is_active proto :ptr

endif

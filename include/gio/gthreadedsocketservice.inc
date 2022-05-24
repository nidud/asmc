ifndef __G_THREADED_SOCKET_SERVICE_H__
define __G_THREADED_SOCKET_SERVICE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsocketservice.inc

define G_TYPE_THREADED_SOCKET_SERVICE                      <g_threaded_socket_service_get_type ()>
G_THREADED_SOCKET_SERVICE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_THREADED_SOCKET_SERVICE, GThreadedSocketService))>
  endm
G_THREADED_SOCKET_SERVICE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_THREADED_SOCKET_SERVICE, GThreadedSocketServiceClass))>
  endm
G_IS_THREADED_SOCKET_SERVICE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_THREADED_SOCKET_SERVICE))>
  endm
G_IS_THREADED_SOCKET_SERVICE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_THREADED_SOCKET_SERVICE))>
  endm
G_THREADED_SOCKET_SERVICE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_THREADED_SOCKET_SERVICE, GThreadedSocketServiceClass))>
  endm

;GThreadedSocketServicePrivate typedef _GThreadedSocketServicePrivate

_GThreadedSocketServiceClass struct
parent_class            GSocketServiceClass <>
run                     proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GThreadedSocketServiceClass ends
GThreadedSocketServiceClass typedef _GThreadedSocketServiceClass

_GThreadedSocketService struct
parent_instance         GSocketService <>
priv                    ptr GThreadedSocketServicePrivate ?
_GThreadedSocketService ends
GThreadedSocketService  typedef _GThreadedSocketService

g_threaded_socket_service_get_type proto
g_threaded_socket_service_new proto :sdword

endif

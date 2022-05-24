ifndef __G_SOCKET_H__
define __G_SOCKET_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET                                       <g_socket_get_type ()>
G_SOCKET macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET, GSocket))>
  endm
G_SOCKET_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET, GSocketClass))>
  endm
G_IS_SOCKET macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET))>
  endm
G_IS_SOCKET_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET))>
  endm
G_SOCKET_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET, GSocketClass))>
  endm

;GSocketPrivate          typedef _GSocketPrivate

_GSocketClass           struct
parent_class            GObjectClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
_g_reserved8            proc
_g_reserved9            proc
_g_reserved10           proc
_GSocketClass           ends
GSocketClass            typedef _GSocketClass

_GSocket                struct
parent_instance         GObject <>
priv                    ptr GSocketPrivate ?
_GSocket                ends
GSocket                 typedef _GSocket

g_socket_get_type proto
g_socket_new proto :GSocketFamily, :GSocketType, :GSocketProtocol, :ptr
g_socket_new_from_fd proto :gint, :ptr
g_socket_get_fd proto :ptr
g_socket_get_family proto :ptr
g_socket_get_socket_type proto :ptr
g_socket_get_protocol proto :ptr
g_socket_get_local_address proto :ptr, :ptr
g_socket_get_remote_address proto :ptr, :ptr
g_socket_set_blocking proto :ptr, :gboolean
g_socket_get_blocking proto :ptr
g_socket_set_keepalive proto :ptr, :gboolean
g_socket_get_keepalive proto :ptr
g_socket_get_listen_backlog proto :ptr
g_socket_set_listen_backlog proto :ptr, :gint
g_socket_get_timeout proto :ptr
g_socket_set_timeout proto :ptr, :guint

g_socket_get_ttl proto :ptr
g_socket_set_ttl proto :ptr, :guint

g_socket_get_broadcast proto :ptr
g_socket_set_broadcast proto :ptr, :gboolean

g_socket_get_multicast_loopback proto :ptr
g_socket_set_multicast_loopback proto :ptr, :gboolean
g_socket_get_multicast_ttl proto :ptr
g_socket_set_multicast_ttl proto :ptr, :guint
g_socket_is_connected proto :ptr
g_socket_bind proto :ptr, :ptr, :gboolean, :ptr
g_socket_join_multicast_group proto :ptr, :ptr, :gboolean, :ptr, :ptr
g_socket_leave_multicast_group proto :ptr, :ptr, :gboolean, :ptr, :ptr
g_socket_join_multicast_group_ssm proto :ptr, :ptr, :ptr, :ptr, :ptr
g_socket_leave_multicast_group_ssm proto :ptr, :ptr, :ptr, :ptr, :ptr
g_socket_connect proto :ptr, :ptr, :ptr, :ptr
g_socket_check_connect_result proto :ptr, :ptr

g_socket_get_available_bytes proto :ptr

g_socket_condition_check proto :ptr, :GIOCondition
g_socket_condition_wait proto :ptr, :GIOCondition, :ptr, :ptr
g_socket_condition_timed_wait proto :ptr, :GIOCondition, :gint64, :ptr, :ptr
g_socket_accept proto :ptr, :ptr, :ptr
g_socket_listen proto :ptr, :ptr
g_socket_receive proto :ptr, :ptr, :gsize, :ptr, :ptr
g_socket_receive_from proto :ptr, :ptr, :ptr, :gsize, :ptr, :ptr
g_socket_send proto :ptr, :ptr, :gsize, :ptr, :ptr
g_socket_send_to proto :ptr, :ptr, :ptr, :gsize, :ptr, :ptr
g_socket_receive_message proto :ptr, :ptr, :ptr, :gint, :ptr, :ptr, :ptr, :ptr, :ptr
g_socket_send_message proto :ptr, :ptr, :ptr, :gint, :ptr, :gint, :gint, :ptr, :ptr

g_socket_receive_messages proto :ptr, :ptr, :guint, :gint, :ptr, :ptr
g_socket_send_messages proto :ptr, :ptr, :guint, :gint, :ptr, :ptr

g_socket_close proto :ptr, :ptr
g_socket_shutdown proto :ptr, :gboolean, :gboolean, :ptr
g_socket_is_closed proto :ptr
g_socket_create_source proto :ptr, :GIOCondition, :ptr
g_socket_speaks_ipv4 proto :ptr
g_socket_get_credentials proto :ptr, :ptr

g_socket_receive_with_blocking proto :ptr, :ptr, :gsize, :gboolean, :ptr, :ptr
g_socket_send_with_blocking proto :ptr, :ptr, :gsize, :gboolean, :ptr, :ptr
g_socket_send_message_with_timeout proto :ptr, :ptr, :ptr, :gint, :ptr, :gint, :gint, :gint64, :ptr, :ptr, :ptr
g_socket_get_option proto :ptr, :gint, :gint, :ptr, :ptr
g_socket_set_option proto :ptr, :gint, :gint, :gint, :ptr

endif

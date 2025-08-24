ifndef __G_SOCKET_CONTROL_MESSAGE_H__
define __G_SOCKET_CONTROL_MESSAGE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SOCKET_CONTROL_MESSAGE                       <g_socket_control_message_get_type ()>
G_SOCKET_CONTROL_MESSAGE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SOCKET_CONTROL_MESSAGE, GSocketControlMessage))>
  endm
G_SOCKET_CONTROL_MESSAGE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SOCKET_CONTROL_MESSAGE, GSocketControlMessageClass))>
  endm
G_IS_SOCKET_CONTROL_MESSAGE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SOCKET_CONTROL_MESSAGE))>
  endm
G_IS_SOCKET_CONTROL_MESSAGE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SOCKET_CONTROL_MESSAGE))>
  endm
G_SOCKET_CONTROL_MESSAGE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SOCKET_CONTROL_MESSAGE, GSocketControlMessageClass))>
  endm

GSocketControlMessageClass struct
parent_class            GObjectClass <>
get_size                proc :ptr
get_level               proc :ptr
get_type                proc :ptr
serialize               proc :ptr, :gpointer
deserialize             proc :sdword, :sdword, :gsize, :gpointer
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
GSocketControlMessageClass ends

GSocketControlMessage   struct
parent_instance         GObject <>
priv                    ptr GSocketControlMessagePrivate ?
GSocketControlMessage   ends

g_socket_control_message_get_type proto
g_socket_control_message_get_size proto :ptr
g_socket_control_message_get_level proto :ptr
g_socket_control_message_get_msg_type proto :ptr
g_socket_control_message_serialize proto :ptr, :gpointer
g_socket_control_message_deserialize proto :sdword, :sdword, :gsize, :gpointer

endif

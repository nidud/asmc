ifndef __G_TCP_WRAPPER_CONNECTION_H__
define __G_TCP_WRAPPER_CONNECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gtcpconnection.inc


define G_TYPE_TCP_WRAPPER_CONNECTION            <g_tcp_wrapper_connection_get_type ()>
G_TCP_WRAPPER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TCP_WRAPPER_CONNECTION, GTcpWrapperConnection))>
  endm
G_TCP_WRAPPER_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_TCP_WRAPPER_CONNECTION, GTcpWrapperConnectionClass))>
  endm
G_IS_TCP_WRAPPER_CONNECTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TCP_WRAPPER_CONNECTION))>
  endm
G_IS_TCP_WRAPPER_CONNECTION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_TCP_WRAPPER_CONNECTION))>
  endm
G_TCP_WRAPPER_CONNECTION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_TCP_WRAPPER_CONNECTION, GTcpWrapperConnectionClass))>
  endm

GTcpWrapperConnectionClass struct
parent_class            GTcpConnectionClass <>
GTcpWrapperConnectionClass ends

GTcpWrapperConnection   struct
parent_instance         GTcpConnection <>
priv                    ptr GTcpWrapperConnectionPrivate ?
GTcpWrapperConnection   ends

g_tcp_wrapper_connection_get_type proto
g_tcp_wrapper_connection_new proto :ptr, :ptr
g_tcp_wrapper_connection_get_base_io_stream proto :ptr

endif

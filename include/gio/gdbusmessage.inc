ifndef __G_DBUS_MESSAGE_H__
define __G_DBUS_MESSAGE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_DBUS_MESSAGE         <g_dbus_message_get_type ()>
G_DBUS_MESSAGE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_MESSAGE, GDBusMessage))>
  endm
G_IS_DBUS_MESSAGE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_MESSAGE))>
  endm

g_dbus_message_get_type proto
g_dbus_message_new proto
g_dbus_message_new_signal proto :ptr, :ptr, :ptr
g_dbus_message_new_method_call proto :ptr, :ptr, :ptr, :ptr
g_dbus_message_new_method_reply proto :ptr

g_dbus_message_new_method_error_valist proto :ptr, :ptr, :ptr, :va_list
g_dbus_message_new_method_error_literal proto :ptr, :ptr, :ptr
g_dbus_message_print proto :ptr, :guint
g_dbus_message_get_locked proto :ptr
g_dbus_message_lock proto :ptr
g_dbus_message_copy proto :ptr, :ptr
g_dbus_message_get_byte_order proto :ptr
g_dbus_message_set_byte_order proto :ptr, :GDBusMessageByteOrder

g_dbus_message_get_message_type proto :ptr
g_dbus_message_set_message_type proto :ptr, :GDBusMessageType
g_dbus_message_get_flags proto :ptr
g_dbus_message_set_flags proto :ptr, :GDBusMessageFlags
g_dbus_message_get_serial proto :ptr
g_dbus_message_set_serial proto :ptr, :guint32
g_dbus_message_get_header proto :ptr, :GDBusMessageHeaderField
g_dbus_message_set_header proto :ptr, :GDBusMessageHeaderField, :ptr
g_dbus_message_get_header_fields proto :ptr
g_dbus_message_get_body proto :ptr
g_dbus_message_set_body proto :ptr, :ptr
g_dbus_message_get_unix_fd_list proto :ptr
g_dbus_message_set_unix_fd_list proto :ptr, :ptr

g_dbus_message_get_reply_serial proto :ptr
g_dbus_message_set_reply_serial proto :ptr, :guint32

g_dbus_message_get_interface proto :ptr
g_dbus_message_set_interface proto :ptr, :ptr

g_dbus_message_get_member proto :ptr
g_dbus_message_set_member proto :ptr, :ptr

g_dbus_message_get_path proto :ptr
g_dbus_message_set_path proto :ptr, :ptr

g_dbus_message_get_sender proto :ptr
g_dbus_message_set_sender proto :ptr, :ptr

g_dbus_message_get_destination proto :ptr
g_dbus_message_set_destination proto :ptr, :ptr

g_dbus_message_get_error_name proto :ptr
g_dbus_message_set_error_name proto :ptr, :ptr

g_dbus_message_get_signature proto :ptr
g_dbus_message_set_signature proto :ptr, :ptr

g_dbus_message_get_num_unix_fds proto :ptr
g_dbus_message_set_num_unix_fds proto :ptr, :guint32

g_dbus_message_get_arg0 proto :ptr

g_dbus_message_new_from_blob proto :ptr, :gsize, :GDBusCapabilityFlags, :ptr
g_dbus_message_bytes_needed proto :ptr, :gsize, :ptr
g_dbus_message_to_blob proto :ptr, :ptr, :GDBusCapabilityFlags, :ptr
g_dbus_message_to_gerror proto :ptr, :ptr

endif

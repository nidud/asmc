ifndef __G_DBUS_METHOD_INVOCATION_H__
define __G_DBUS_METHOD_INVOCATION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_DBUS_METHOD_INVOCATION         <g_dbus_method_invocation_get_type ()>
G_DBUS_METHOD_INVOCATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_METHOD_INVOCATION, GDBusMethodInvocation))>
  endm
G_IS_DBUS_METHOD_INVOCATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_METHOD_INVOCATION))>
  endm

define G_DBUS_METHOD_INVOCATION_HANDLED TRUE ;GLIB_AVAILABLE_MACRO_IN_2_68
define G_DBUS_METHOD_INVOCATION_UNHANDLED FALSE ;GLIB_AVAILABLE_MACRO_IN_2_68

g_dbus_method_invocation_get_type proto
g_dbus_method_invocation_get_sender proto :ptr
g_dbus_method_invocation_get_object_path proto :ptr
g_dbus_method_invocation_get_interface_name proto :ptr
g_dbus_method_invocation_get_method_name proto :ptr
g_dbus_method_invocation_get_method_info proto :ptr
g_dbus_method_invocation_get_property_info proto :ptr
g_dbus_method_invocation_get_connection proto :ptr
g_dbus_method_invocation_get_message proto :ptr
g_dbus_method_invocation_get_parameters proto :ptr
g_dbus_method_invocation_get_user_data proto :ptr

g_dbus_method_invocation_return_value proto :ptr, :ptr
g_dbus_method_invocation_return_value_with_unix_fd_list proto :ptr, :ptr, :ptr


g_dbus_method_invocation_return_error_literal proto :ptr, :GQuark, :gint, :ptr
g_dbus_method_invocation_return_gerror proto :ptr, :ptr
g_dbus_method_invocation_take_error proto :ptr, :ptr
g_dbus_method_invocation_return_dbus_error proto :ptr, :ptr, :ptr


endif

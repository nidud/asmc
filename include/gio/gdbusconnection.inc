ifndef __G_DBUS_CONNECTION_H__
define __G_DBUS_CONNECTION_H__

if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_DBUS_CONNECTION <g_dbus_connection_get_type ()>
G_DBUS_CONNECTION macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_CONNECTION, GDBusConnection))>
	endm
G_IS_DBUS_CONNECTION macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_CONNECTION))>
	endm

g_dbus_connection_get_type proto __cdecl
g_bus_get proto __cdecl :GBusType, :ptr, :GAsyncReadyCallback, :gpointer
g_bus_get_finish proto __cdecl :ptr, :ptr
g_bus_get_sync proto __cdecl :GBusType, :ptr, :ptr
g_dbus_connection_new proto __cdecl :ptr, :ptr, :GDBusConnectionFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_new_finish proto __cdecl :ptr, :ptr
g_dbus_connection_new_sync proto __cdecl :ptr, :ptr, :GDBusConnectionFlags, :ptr, :ptr, :ptr
g_dbus_connection_new_for_address proto __cdecl :ptr, :GDBusConnectionFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_new_for_address_finish proto __cdecl :ptr, :ptr
g_dbus_connection_new_for_address_sync proto __cdecl :ptr, :GDBusConnectionFlags, :ptr, :ptr, :ptr
g_dbus_connection_start_message_processing proto __cdecl :ptr
g_dbus_connection_is_closed proto __cdecl :ptr
g_dbus_connection_get_stream proto __cdecl :ptr
g_dbus_connection_get_guid proto __cdecl :ptr
g_dbus_connection_get_unique_name proto __cdecl :ptr
g_dbus_connection_get_peer_credentials proto __cdecl :ptr
g_dbus_connection_get_last_serial proto __cdecl :ptr
g_dbus_connection_get_exit_on_close proto __cdecl :ptr
g_dbus_connection_set_exit_on_close proto __cdecl :ptr, :gboolean
g_dbus_connection_get_capabilities proto __cdecl :ptr
g_dbus_connection_get_flags proto __cdecl :ptr
g_dbus_connection_close proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_close_finish proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_close_sync proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_flush proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_flush_finish proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_flush_sync proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_send_message proto __cdecl :ptr, :ptr, :GDBusSendMessageFlags, :ptr, :ptr
g_dbus_connection_send_message_with_reply proto __cdecl :ptr, :ptr, :GDBusSendMessageFlags, :gint, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_send_message_with_reply_finish proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_send_message_with_reply_sync proto __cdecl :ptr, :ptr, :GDBusSendMessageFlags, :gint, :ptr, :ptr, :ptr
g_dbus_connection_emit_signal proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_dbus_connection_call proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_call_finish proto __cdecl :ptr, :ptr, :ptr
g_dbus_connection_call_sync proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr
g_dbus_connection_call_with_unix_fd_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_connection_call_with_unix_fd_list_finish proto __cdecl :ptr, :ptr, :ptr, :ptr
g_dbus_connection_call_with_unix_fd_list_sync proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr, :ptr, :ptr

CALLBACKC(GDBusInterfaceMethodCallFunc, :ptr, :ptr, :ptr,  :ptr, :ptr, :ptr, :ptr, :gpointer)
CALLBACKC(GDBusInterfaceGetPropertyFunc, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :gpointer)
CALLBACKC(GDBusInterfaceSetPropertyFunc, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :gpointer)

GDBusInterfaceVTable	STRUC
method_call		GDBusInterfaceMethodCallFunc ?
get_property		GDBusInterfaceGetPropertyFunc ?
set_property		GDBusInterfaceSetPropertyFunc ?
padding			gpointer 8 dup(?)
GDBusInterfaceVTable	ENDS

g_dbus_connection_register_object proto __cdecl :ptr, :ptr, :ptr, :ptr, :gpointer, :GDestroyNotify, :ptr
g_dbus_connection_register_object_with_closures proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_dbus_connection_unregister_object proto __cdecl :ptr, :guint

CALLBACKC(GDBusSubtreeEnumerateFunc, :ptr, :ptr, :ptr, :gpointer)
CALLBACKC(GDBusSubtreeIntrospectFunc, :ptr, :ptr, :ptr, :ptr, :gpointer)
CALLBACKC(GDBusSubtreeDispatchFunc, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :gpointer)

GDBusSubtreeVTable	STRUC
enumerate		GDBusSubtreeEnumerateFunc ?
introspect		GDBusSubtreeIntrospectFunc ?
dispatch		GDBusSubtreeDispatchFunc ?
padding			gpointer 8 dup(?)
GDBusSubtreeVTable	ENDS

g_dbus_connection_register_subtree proto __cdecl :ptr, :ptr, :ptr, :GDBusSubtreeFlags, :gpointer, :GDestroyNotify, :ptr
g_dbus_connection_unregister_subtree proto __cdecl :ptr, :guint

CALLBACKC(GDBusSignalCallback, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :gpointer)

g_dbus_connection_signal_subscribe proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GDBusSignalFlags, :GDBusSignalCallback, :gpointer, :GDestroyNotify
g_dbus_connection_signal_unsubscribe proto __cdecl :ptr, :guint

CALLBACKC(GDBusMessageFilterFunction, :ptr, :ptr, :gboolean, :gpointer)

g_dbus_connection_add_filter proto __cdecl :ptr, :GDBusMessageFilterFunction, :gpointer, :GDestroyNotify
g_dbus_connection_remove_filter proto __cdecl :ptr, :guint

endif

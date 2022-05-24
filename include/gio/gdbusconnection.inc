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

;GType
g_dbus_connection_get_type proto __cdecl


;void
g_bus_get proto __cdecl \
	      bus_type: GBusType,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GDBusConnection
g_bus_get_finish proto __cdecl \
		   res: ptr GAsyncResult,
		 error: ptr GError

;GDBusConnection
g_bus_get_sync proto __cdecl \
	      bus_type: GBusType,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_dbus_connection_new proto __cdecl \
		stream: ptr GIOStream,
		  guid: ptr gchar,
		 flags: GDBusConnectionFlags,
	      observer: ptr GDBusAuthObserver,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GDBusConnection
g_dbus_connection_new_finish proto __cdecl \
		   res: ptr GAsyncResult,
		 error: ptr GError

;GDBusConnection
g_dbus_connection_new_sync proto __cdecl \
		stream: ptr GIOStream,
		  guid: ptr gchar,
		 flags: GDBusConnectionFlags,
	      observer: ptr GDBusAuthObserver,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_dbus_connection_new_for_address proto __cdecl \
	       address: ptr gchar,
		 flags: GDBusConnectionFlags,
	      observer: ptr GDBusAuthObserver,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GDBusConnection
g_dbus_connection_new_for_address_finish proto __cdecl \
		   res: ptr GAsyncResult,
		 error: ptr GError

;GDBusConnection
g_dbus_connection_new_for_address_sync proto __cdecl \
	       address: ptr gchar,
		 flags: GDBusConnectionFlags,
	      observer: ptr GDBusAuthObserver,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_dbus_connection_start_message_processing proto __cdecl \
	    connection: ptr GDBusConnection

;gboolean
g_dbus_connection_is_closed proto __cdecl \
	    connection: ptr GDBusConnection

;GIOStream
g_dbus_connection_get_stream proto __cdecl \
	    connection: ptr GDBusConnection

;const
g_dbus_connection_get_guid proto __cdecl \
	    connection: ptr GDBusConnection

;const
g_dbus_connection_get_unique_name proto __cdecl \
	    connection: ptr GDBusConnection

;GCredentials
g_dbus_connection_get_peer_credentials proto __cdecl \
	    connection: ptr GDBusConnection


;guint32
g_dbus_connection_get_last_serial proto __cdecl \
	    connection: ptr GDBusConnection


;gboolean
g_dbus_connection_get_exit_on_close proto __cdecl \
	    connection: ptr GDBusConnection

;void
g_dbus_connection_set_exit_on_close proto __cdecl \
	    connection: ptr GDBusConnection,
	 exit_on_close: gboolean

;GDBusCapabilityFlags
g_dbus_connection_get_capabilities proto __cdecl \
	    connection: ptr GDBusConnection

;GDBusConnectionFlags
g_dbus_connection_get_flags proto __cdecl \
	    connection: ptr GDBusConnection

;void
g_dbus_connection_close proto __cdecl \
	    connection: ptr GDBusConnection,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_dbus_connection_close_finish proto __cdecl \
	    connection: ptr GDBusConnection,
		   res: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_dbus_connection_close_sync proto __cdecl \
	    connection: ptr GDBusConnection,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_dbus_connection_flush proto __cdecl \
	    connection: ptr GDBusConnection,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;gboolean
g_dbus_connection_flush_finish proto __cdecl \
	    connection: ptr GDBusConnection,
		   res: ptr GAsyncResult,
		 error: ptr GError

;gboolean
g_dbus_connection_flush_sync proto __cdecl \
	    connection: ptr GDBusConnection,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;gboolean
g_dbus_connection_send_message proto __cdecl \
	    connection: ptr GDBusConnection,
	       message: ptr GDBusMessage,
		 flags: GDBusSendMessageFlags,
	    out_serial: ptr guint32,
		 error: ptr GError

;void
g_dbus_connection_send_message_with_reply proto __cdecl \
	    connection: ptr GDBusConnection,
	       message: ptr GDBusMessage,
		 flags: GDBusSendMessageFlags,
	  timeout_msec: gint,
	    out_serial: ptr guint32,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GDBusMessage
g_dbus_connection_send_message_with_reply_finish proto __cdecl \
	    connection: ptr GDBusConnection,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GDBusMessage
g_dbus_connection_send_message_with_reply_sync proto __cdecl \
	    connection: ptr GDBusConnection,
	       message: ptr GDBusMessage,
		 flags: GDBusSendMessageFlags,
	  timeout_msec: gint,
	    out_serial: ptr guint32,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;gboolean
g_dbus_connection_emit_signal proto __cdecl \
	    connection: ptr GDBusConnection,
  destination_bus_name: ptr gchar,
	   object_path: ptr gchar,
	interface_name: ptr gchar,
	   signal_name: ptr gchar,
	    parameters: ptr GVariant,
		 error: ptr GError

;void
g_dbus_connection_call proto __cdecl \
	    connection: ptr GDBusConnection,
	      bus_name: ptr gchar,
	   object_path: ptr gchar,
	interface_name: ptr gchar,
	   method_name: ptr gchar,
	    parameters: ptr GVariant,
	    reply_type: ptr GVariantType,
		 flags: GDBusCallFlags,
	  timeout_msec: gint,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GVariant
g_dbus_connection_call_finish proto __cdecl \
	    connection: ptr GDBusConnection,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GVariant
g_dbus_connection_call_sync proto __cdecl \
	    connection: ptr GDBusConnection,
	      bus_name: ptr gchar,
	   object_path: ptr gchar,
	interface_name: ptr gchar,
	   method_name: ptr gchar,
	    parameters: ptr GVariant,
	    reply_type: ptr GVariantType,
		 flags: GDBusCallFlags,
	  timeout_msec: gint,
	   cancellable: ptr GCancellable,
		 error: ptr GError

;void
g_dbus_connection_call_with_unix_fd_list proto __cdecl \
	    connection: ptr GDBusConnection,
	      bus_name: ptr gchar,
	   object_path: ptr gchar,
	interface_name: ptr gchar,
	   method_name: ptr gchar,
	    parameters: ptr GVariant,
	    reply_type: ptr GVariantType,
		 flags: GDBusCallFlags,
	  timeout_msec: gint,
	       fd_list: ptr GUnixFDList,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GVariant
g_dbus_connection_call_with_unix_fd_list_finish proto __cdecl \
	    connection: ptr GDBusConnection,
	   out_fd_list: ptr GUnixFDList,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GVariant
g_dbus_connection_call_with_unix_fd_list_sync proto __cdecl \
	    connection: ptr GDBusConnection,
	      bus_name: ptr gchar,
	   object_path: ptr gchar,
	interface_name: ptr gchar,
	   method_name: ptr gchar,
	    parameters: ptr GVariant,
	    reply_type: ptr GVariantType,
		 flags: GDBusCallFlags,
	  timeout_msec: gint,
	       fd_list: ptr GUnixFDList,
	   out_fd_list: ptr GUnixFDList,
	   cancellable: ptr GCancellable,
		 error: ptr GError

CALLBACKC(GDBusInterfaceMethodCallFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar,  :ptr gchar, :ptr gchar, :ptr GVariant, :ptr GDBusMethodInvocation, :gpointer)
CALLBACKC(GDBusInterfaceGetPropertyFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :ptr gchar, :ptr gchar, :ptr ptr GError, :gpointer)
CALLBACKC(GDBusInterfaceSetPropertyFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :ptr gchar, :ptr gchar, :ptr GVariant, :ptr ptr GError, :gpointer)

GDBusInterfaceVTable	STRUC
method_call		GDBusInterfaceMethodCallFunc ?
get_property		GDBusInterfaceGetPropertyFunc ?
set_property		GDBusInterfaceSetPropertyFunc ?
padding			gpointer 8 dup(?)
GDBusInterfaceVTable	ENDS

;guint
g_dbus_connection_register_object proto __cdecl \
	    connection: ptr GDBusConnection,
	   object_path: ptr gchar,
	interface_info: ptr GDBusInterfaceInfo,
		vtable: ptr GDBusInterfaceVTable,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify,
		 error: ptr GError

;guint
g_dbus_connection_register_object_with_closures proto __cdecl \
	    connection: ptr GDBusConnection,
	   object_path: ptr gchar,
	interface_info: ptr GDBusInterfaceInfo,
   method_call_closure: ptr GClosure,
  get_property_closure: ptr GClosure,
  set_property_closure: ptr GClosure,
		 error: ptr GError

;gboolean
g_dbus_connection_unregister_object proto __cdecl \
	    connection: ptr GDBusConnection,
       registration_id: guint


CALLBACKC(GDBusSubtreeEnumerateFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :gpointer)
CALLBACKC(GDBusSubtreeIntrospectFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :ptr gchar, :gpointer)
CALLBACKC(GDBusSubtreeDispatchFunc, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :ptr gchar, :ptr gchar, :ptr gpointer, :gpointer)

GDBusSubtreeVTable	STRUC
enumerate		GDBusSubtreeEnumerateFunc ?
introspect		GDBusSubtreeIntrospectFunc ?
dispatch		GDBusSubtreeDispatchFunc ?
padding			gpointer 8 dup(?)
GDBusSubtreeVTable	ENDS

;guint
g_dbus_connection_register_subtree proto __cdecl \
	    connection: ptr GDBusConnection,
	   object_path: ptr gchar,
		vtable: ptr GDBusSubtreeVTable,
		 flags: GDBusSubtreeFlags,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify,
		 error: ptr GError

;gboolean
g_dbus_connection_unregister_subtree proto __cdecl \
	    connection: ptr GDBusConnection,
       registration_id: guint


CALLBACKC(GDBusSignalCallback, :ptr GDBusConnection, :ptr gchar, :ptr gchar, :ptr gchar, :ptr gchar, :ptr GVariant, :gpointer)

;guint
g_dbus_connection_signal_subscribe proto __cdecl \
	    connection: ptr GDBusConnection,
		sender: ptr gchar,
	interface_name: ptr gchar,
		member: ptr gchar,
	   object_path: ptr gchar,
		  arg0: ptr gchar,
		 flags: GDBusSignalFlags,
	      callback: GDBusSignalCallback,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify

;void
g_dbus_connection_signal_unsubscribe proto __cdecl \
	    connection: ptr GDBusConnection,
       subscription_id: guint


CALLBACKC(GDBusMessageFilterFunction, :ptr GDBusConnection, :ptr GDBusMessage, :gboolean, :gpointer)

;guint
g_dbus_connection_add_filter proto __cdecl \
	    connection: ptr GDBusConnection,
       filter_function: GDBusMessageFilterFunction,
	     user_data: gpointer,
   user_data_free_func: GDestroyNotify


;void
g_dbus_connection_remove_filter proto __cdecl \
	    connection: ptr GDBusConnection,
	     filter_id: guint

endif

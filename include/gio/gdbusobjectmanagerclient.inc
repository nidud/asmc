ifndef __G_DBUS_OBJECT_MANAGER_CLIENT_H__
define __G_DBUS_OBJECT_MANAGER_CLIENT_H__

include gio/giotypes.inc


define G_TYPE_DBUS_OBJECT_MANAGER_CLIENT         <g_dbus_object_manager_client_get_type ()>
G_DBUS_OBJECT_MANAGER_CLIENT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT_MANAGER_CLIENT, GDBusObjectManagerClient))>
  endm
G_DBUS_OBJECT_MANAGER_CLIENT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_OBJECT_MANAGER_CLIENT, GDBusObjectManagerClientClass))>
  endm
G_DBUS_OBJECT_MANAGER_CLIENT_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_OBJECT_MANAGER_CLIENT, GDBusObjectManagerClientClass))>
  endm
G_IS_DBUS_OBJECT_MANAGER_CLIENT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT_MANAGER_CLIENT))>
  endm
G_IS_DBUS_OBJECT_MANAGER_CLIENT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_OBJECT_MANAGER_CLIENT))>
  endm

GDBusObjectManagerClient struct
parent_instance         GObject <>
priv                    ptr GDBusObjectManagerClientPrivate ?
GDBusObjectManagerClient ends

GDBusObjectManagerClientClass struct
parent_class            GObjectClass <>
interface_proxy_signal  proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
interface_proxy_properties_changed proc :ptr, :ptr, :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
GDBusObjectManagerClientClass ends

g_dbus_object_manager_client_get_type proto
g_dbus_object_manager_client_new proto :ptr, :GDBusObjectManagerClientFlags, :ptr, :ptr, :GDBusProxyTypeFunc, :gpointer, :GDestroyNotify, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_object_manager_client_new_finish proto :ptr, :ptr
g_dbus_object_manager_client_new_sync proto :ptr, :GDBusObjectManagerClientFlags, :ptr, :ptr, :GDBusProxyTypeFunc, :gpointer, :GDestroyNotify, :ptr, :ptr
g_dbus_object_manager_client_new_for_bus proto :GBusType, :GDBusObjectManagerClientFlags, :ptr, :ptr, :GDBusProxyTypeFunc, :gpointer, :GDestroyNotify, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_object_manager_client_new_for_bus_finish proto :ptr, :ptr
g_dbus_object_manager_client_new_for_bus_sync proto :GBusType, :GDBusObjectManagerClientFlags, :ptr, :ptr, :GDBusProxyTypeFunc, :gpointer, :GDestroyNotify, :ptr, :ptr
g_dbus_object_manager_client_get_connection proto :ptr
g_dbus_object_manager_client_get_flags proto :ptr
g_dbus_object_manager_client_get_name proto :ptr
g_dbus_object_manager_client_get_name_owner proto :ptr

endif

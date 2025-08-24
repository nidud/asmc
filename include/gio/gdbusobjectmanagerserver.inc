ifndef __G_DBUS_OBJECT_MANAGER_SERVER_H__
define __G_DBUS_OBJECT_MANAGER_SERVER_H__

include gio/giotypes.inc

define G_TYPE_DBUS_OBJECT_MANAGER_SERVER         <g_dbus_object_manager_server_get_type ()>
G_DBUS_OBJECT_MANAGER_SERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT_MANAGER_SERVER, GDBusObjectManagerServer))>
  endm
G_DBUS_OBJECT_MANAGER_SERVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_OBJECT_MANAGER_SERVER, GDBusObjectManagerServerClass))>
  endm
G_DBUS_OBJECT_MANAGER_SERVER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_OBJECT_MANAGER_SERVER, GDBusObjectManagerServerClass))>
  endm
G_IS_DBUS_OBJECT_MANAGER_SERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT_MANAGER_SERVER))>
  endm
G_IS_DBUS_OBJECT_MANAGER_SERVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_OBJECT_MANAGER_SERVER))>
  endm

GDBusObjectManagerServer struct
parent_instance         GObject <>
priv                    ptr GDBusObjectManagerServerPrivate ?
GDBusObjectManagerServer ends

GDBusObjectManagerServerClass struct
parent_class            GObjectClass <>
padding                 gpointer 8 dup(?)
GDBusObjectManagerServerClass ends

g_dbus_object_manager_server_get_type proto
g_dbus_object_manager_server_new proto :ptr
g_dbus_object_manager_server_get_connection proto :ptr
g_dbus_object_manager_server_set_connection proto :ptr, :ptr
g_dbus_object_manager_server_export proto :ptr, :ptr
g_dbus_object_manager_server_export_uniquely proto :ptr, :ptr
g_dbus_object_manager_server_is_exported proto :ptr, :ptr
g_dbus_object_manager_server_unexport proto :ptr, :ptr

endif

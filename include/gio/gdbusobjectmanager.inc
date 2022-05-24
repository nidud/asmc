ifndef __G_DBUS_OBJECT_MANAGER_H__
define __G_DBUS_OBJECT_MANAGER_H__

include gio/giotypes.inc

define G_TYPE_DBUS_OBJECT_MANAGER         <g_dbus_object_manager_get_type ()>
G_DBUS_OBJECT_MANAGER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT_MANAGER, GDBusObjectManager))>
  endm
G_IS_DBUS_OBJECT_MANAGER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT_MANAGER))>
  endm
G_DBUS_OBJECT_MANAGER_GET_IFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE((o), G_TYPE_DBUS_OBJECT_MANAGER, GDBusObjectManagerIface))>
  endm

_GDBusObjectManagerIface struct
parent_iface            GTypeInterface <>
get_object_path         proc :ptr
get_objects             proc :ptr
get_object              proc :ptr, :ptr
get_interface           proc :ptr, :ptr, :ptr
object_added            proc :ptr, :ptr
object_removed          proc :ptr, :ptr
interface_added         proc :ptr, :ptr, :ptr
interface_removed       proc :ptr, :ptr, :ptr
_GDBusObjectManagerIface ends
GDBusObjectManagerIface typedef _GDBusObjectManagerIface

g_dbus_object_manager_get_type proto
g_dbus_object_manager_get_object_path proto :ptr
g_dbus_object_manager_get_objects proto :ptr
g_dbus_object_manager_get_object proto :ptr, :ptr
g_dbus_object_manager_get_interface proto :ptr, :ptr, :ptr

endif

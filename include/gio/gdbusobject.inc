ifndef __G_DBUS_OBJECT_H__
define __G_DBUS_OBJECT_H__

include gio/giotypes.inc

define G_TYPE_DBUS_OBJECT         <g_dbus_object_get_type ()>
G_DBUS_OBJECT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT, GDBusObject))>
  endm
G_IS_DBUS_OBJECT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT))>
  endm
G_DBUS_OBJECT_GET_IFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE((o), G_TYPE_DBUS_OBJECT, GDBusObjectIface))>
  endm

GDBusObjectIface        struct
parent_iface            GTypeInterface <>
get_object_path         proc :ptr
get_interfaces          proc :ptr
get_interface           proc :ptr, :ptr
interface_added         proc :ptr, :ptr
interface_removed       proc :ptr, :ptr
GDBusObjectIface        ends

g_dbus_object_get_type proto
g_dbus_object_get_object_path proto :ptr
g_dbus_object_get_interfaces proto :ptr
g_dbus_object_get_interface proto :ptr, :ptr

endif

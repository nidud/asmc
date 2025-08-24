ifndef __G_DBUS_INTERFACE_H__
define __G_DBUS_INTERFACE_H__

include gio/giotypes.inc

define G_TYPE_DBUS_INTERFACE         <g_dbus_interface_get_type ()>
G_DBUS_INTERFACE macro o
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_INTERFACE, GDBusInterface)>
  endm
G_IS_DBUS_INTERFACE macro o
  exitm<G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_INTERFACE)>
  endm
G_DBUS_INTERFACE_GET_IFACE macro o
  exitm<G_TYPE_INSTANCE_GET_INTERFACE((o), G_TYPE_DBUS_INTERFACE, GDBusInterfaceIface)>
  endm

GDBusInterfaceIface     struct
parent_iface            GTypeInterface <>
get_info                proc :ptr
get_object              proc :ptr
set_object              proc :ptr, :ptr
dup_object              proc :ptr
GDBusInterfaceIface     ends

g_dbus_interface_get_type proto
g_dbus_interface_get_info proto :ptr
g_dbus_interface_get_object proto :ptr
g_dbus_interface_set_object proto :ptr, :ptr
g_dbus_interface_dup_object proto :ptr

endif

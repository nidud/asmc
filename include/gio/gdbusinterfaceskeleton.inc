ifndef __G_DBUS_INTERFACE_SKELETON_H__
define __G_DBUS_INTERFACE_SKELETON_H__

include gio/giotypes.inc

define G_TYPE_DBUS_INTERFACE_SKELETON         <g_dbus_interface_skeleton_get_type>
G_DBUS_INTERFACE_SKELETON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_INTERFACE_SKELETON, GDBusInterfaceSkeleton))>
  endm
G_DBUS_INTERFACE_SKELETON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_INTERFACE_SKELETON, GDBusInterfaceSkeletonClass))>
  endm
G_DBUS_INTERFACE_SKELETON_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_INTERFACE_SKELETON, GDBusInterfaceSkeletonClass))>
  endm
G_IS_DBUS_INTERFACE_SKELETON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_INTERFACE_SKELETON))>
  endm
G_IS_DBUS_INTERFACE_SKELETON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_INTERFACE_SKELETON))>
  endm

;GDBusInterfaceSkeletonPrivate typedef _GDBusInterfaceSkeletonPrivate

_GDBusInterfaceSkeleton struct
parent_instance         GObject <>
priv                    ptr GDBusInterfaceSkeletonPrivate ?
_GDBusInterfaceSkeleton ends

_GDBusInterfaceSkeletonClass struct
parent_class            GObjectClass <>
get_info                proc :ptr
get_vtable              proc :ptr
get_properties          proc :ptr
flush                   proc :ptr
vfunc_padding           gpointer 8 dup(?)
g_authorize_method      proc :ptr, :ptr
signal_padding          gpointer 8 dup(?)
_GDBusInterfaceSkeletonClass ends
GDBusInterfaceSkeletonClass typedef _GDBusInterfaceSkeletonClass

g_dbus_interface_skeleton_get_type proto
g_dbus_interface_skeleton_get_flags proto :ptr
g_dbus_interface_skeleton_set_flags proto :ptr, :GDBusInterfaceSkeletonFlags
g_dbus_interface_skeleton_get_info proto :ptr
g_dbus_interface_skeleton_get_vtable proto :ptr
g_dbus_interface_skeleton_get_properties proto :ptr
g_dbus_interface_skeleton_flush proto :ptr

g_dbus_interface_skeleton_export proto :ptr, :ptr, :ptr, :ptr
g_dbus_interface_skeleton_unexport proto :ptr
g_dbus_interface_skeleton_unexport_from_connection proto :ptr, :ptr

g_dbus_interface_skeleton_get_connection proto :ptr
g_dbus_interface_skeleton_get_connections proto :ptr
g_dbus_interface_skeleton_has_connection proto :ptr, :ptr
g_dbus_interface_skeleton_get_object_path proto :ptr

endif

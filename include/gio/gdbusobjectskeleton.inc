ifndef __G_DBUS_OBJECT_SKELETON_H__
define __G_DBUS_OBJECT_SKELETON_H__

include gio/giotypes.inc

define G_TYPE_DBUS_OBJECT_SKELETON         <g_dbus_object_skeleton_get_type ()>
G_DBUS_OBJECT_SKELETON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT_SKELETON, GDBusObjectSkeleton))>
  endm
G_DBUS_OBJECT_SKELETON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_OBJECT_SKELETON, GDBusObjectSkeletonClass))>
  endm
G_DBUS_OBJECT_SKELETON_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_OBJECT_SKELETON, GDBusObjectSkeletonClass))>
  endm
G_IS_DBUS_OBJECT_SKELETON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT_SKELETON))>
  endm
G_IS_DBUS_OBJECT_SKELETON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_OBJECT_SKELETON))>
  endm

;GDBusObjectSkeletonPrivate typedef _GDBusObjectSkeletonPrivate

_GDBusObjectSkeleton    struct
parent_instance         GObject <>
priv                    ptr GDBusObjectSkeletonPrivate ?
_GDBusObjectSkeleton    ends
GDBusObjectSkeleton     typedef _GDBusObjectSkeleton

_GDBusObjectSkeletonClass struct
parent_class            GObjectClass <>
authorize_method        proc :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
_GDBusObjectSkeletonClass ends
GDBusObjectSkeletonClass typedef _GDBusObjectSkeletonClass

g_dbus_object_skeleton_get_type proto
g_dbus_object_skeleton_new proto :ptr
g_dbus_object_skeleton_flush proto :ptr
g_dbus_object_skeleton_add_interface proto :ptr, :ptr
g_dbus_object_skeleton_remove_interface proto :ptr, :ptr
g_dbus_object_skeleton_remove_interface_by_name proto :ptr, :ptr
g_dbus_object_skeleton_set_object_path proto :ptr, :ptr

endif

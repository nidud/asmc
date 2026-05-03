ifndef __G_PERMISSION_H__
define __G_PERMISSION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_PERMISSION             <g_permission_get_type ()>
G_PERMISSION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_PERMISSION, GPermission))>
  endm
G_PERMISSION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_PERMISSION, GPermissionClass))>
  endm
G_IS_PERMISSION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_PERMISSION))>
  endm
G_IS_PERMISSION_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_PERMISSION))>
  endm
G_PERMISSION_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_PERMISSION, GPermissionClass))>
  endm

GPermission             struct
parent_instance         GObject <>
priv                    ptr GPermissionPrivate ?
GPermission             ends

GPermissionClass        struct
parent_class            GObjectClass <>
acquire                 proc :ptr, :ptr, :ptr
acquire_async           proc :ptr, :ptr, :GAsyncReadyCallback, :gpointer
acquire_finish          proc :ptr, :ptr, :ptr
release                 proc :ptr, :ptr, :ptr
release_async           proc :ptr, :ptr, :GAsyncReadyCallback, :gpointer
release_finish          proc :ptr, :ptr, :ptr
reserved                gpointer 16 dup(?)
GPermissionClass        ends

g_permission_get_type proto
g_permission_acquire proto :ptr, :ptr, :ptr
g_permission_acquire_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_permission_acquire_finish proto :ptr, :ptr, :ptr

g_permission_release proto :ptr, :ptr, :ptr
g_permission_release_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_permission_release_finish proto :ptr, :ptr, :ptr

g_permission_get_allowed proto :ptr
g_permission_get_can_acquire proto :ptr
g_permission_get_can_release proto :ptr

g_permission_impl_update proto :ptr, :gboolean, :gboolean, :gboolean

endif

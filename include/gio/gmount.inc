ifndef __G_MOUNT_H__
define __G_MOUNT_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_MOUNT            <g_mount_get_type ()>
G_MOUNT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_MOUNT, GMount))>
  endm
G_IS_MOUNT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_MOUNT))>
  endm
G_MOUNT_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_MOUNT, GMountIface))>
  endm

_GMountIface            struct
g_iface                 GTypeInterface <>
changed                 proc :ptr
unmounted               proc :ptr
get_root                proc :ptr
get_name                proc :ptr
get_icon                proc :ptr
get_uuid                proc :ptr
get_volume              proc :ptr
get_drive               proc :ptr
can_unmount             proc :ptr
can_eject               proc :ptr
unmount                 proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
unmount_finish          proc :ptr, :ptr, :ptr
eject                   proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
eject_finish            proc :ptr, :ptr, :ptr
remount                 proc :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
remount_finish          proc :ptr, :ptr, :ptr
guess_content_type      proc :ptr, :gboolean, :ptr, :GAsyncReadyCallback, :gpointer
guess_content_type_finish proc :ptr, :ptr, :ptr
guess_content_type_sync proc :ptr, :gboolean, :ptr, :ptr
pre_unmount             proc :ptr
unmount_with_operation  proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
unmount_with_operation_finish proc :ptr, :ptr, :ptr
eject_with_operation    proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
eject_with_operation_finish proc :ptr, :ptr, :ptr
get_default_location    proc :ptr
get_sort_key            proc :ptr
get_symbolic_icon       proc :ptr
_GMountIface            ends
GMountIface             typedef _GMountIface

g_mount_get_type proto

g_mount_get_root proto :ptr
g_mount_get_default_location proto :ptr
g_mount_get_name proto :ptr
g_mount_get_icon proto :ptr
g_mount_get_symbolic_icon proto :ptr
g_mount_get_uuid proto :ptr
g_mount_get_volume proto :ptr
g_mount_get_drive proto :ptr
g_mount_can_unmount proto :ptr
g_mount_can_eject proto :ptr

g_mount_unmount proto :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_unmount_finish proto :ptr, :ptr, :ptr
g_mount_eject proto :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_eject_finish proto :ptr, :ptr, :ptr
g_mount_remount proto :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_remount_finish proto :ptr, :ptr, :ptr
g_mount_guess_content_type proto :ptr, :gboolean, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_guess_content_type_finish proto :ptr, :ptr, :ptr
g_mount_guess_content_type_sync proto :ptr, :gboolean, :ptr, :ptr

g_mount_is_shadowed proto :ptr
g_mount_shadow proto :ptr
g_mount_unshadow proto :ptr

g_mount_unmount_with_operation proto :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_unmount_with_operation_finish proto :ptr, :ptr, :ptr

g_mount_eject_with_operation proto :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_mount_eject_with_operation_finish proto :ptr, :ptr, :ptr

g_mount_get_sort_key proto :ptr

endif

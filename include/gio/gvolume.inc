ifndef __G_VOLUME_H__
define __G_VOLUME_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_VOLUME_IDENTIFIER_KIND_HAL_UDI <"hal-udi" GLIB_DEPRECATED_MACRO_IN_2_58>
define G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE <"unix-device">
define G_VOLUME_IDENTIFIER_KIND_LABEL <"label">
define G_VOLUME_IDENTIFIER_KIND_UUID <"uuid">
define G_VOLUME_IDENTIFIER_KIND_NFS_MOUNT <"nfs-mount">
define G_VOLUME_IDENTIFIER_KIND_CLASS <"class">

define G_TYPE_VOLUME            <g_volume_get_type ()>
G_VOLUME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_VOLUME, GVolume))>
  endm
G_IS_VOLUME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_VOLUME))>
  endm
G_VOLUME_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_VOLUME, GVolumeIface))>
  endm


GVolumeIface            struct
g_iface                 GTypeInterface <>
changed                 proc :ptr
removed                 proc :ptr
get_name                proc :ptr
get_icon                proc :ptr
get_uuid                proc :ptr
get_drive               proc :ptr
get_mount               proc :ptr
can_mount               proc :ptr
can_eject               proc :ptr
mount_fn                proc :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
mount_finish            proc :ptr, :ptr, :ptr
eject                   proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
eject_finish            proc :ptr, :ptr, :ptr
get_identifier          proc :ptr, :ptr
enumerate_identifiers   proc :ptr
should_automount        proc :ptr
get_activation_root     proc :ptr
eject_with_operation    proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
eject_with_operation_finish proc :ptr, :ptr, :ptr
get_sort_key            proc :ptr
get_symbolic_icon       proc :ptr
GVolumeIface            ends


g_volume_get_type proto
g_volume_get_name proto :ptr
g_volume_get_icon proto :ptr
g_volume_get_symbolic_icon proto :ptr
g_volume_get_uuid proto :ptr
g_volume_get_drive proto :ptr
g_volume_get_mount proto :ptr
g_volume_can_mount proto :ptr
g_volume_can_eject proto :ptr
g_volume_should_automount proto :ptr
g_volume_mount proto :ptr, :GMountMountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_volume_mount_finish proto :ptr, :ptr, :ptr
g_volume_eject proto :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_volume_eject_finish proto :ptr, :ptr, :ptr
g_volume_get_identifier proto :ptr, :ptr
g_volume_enumerate_identifiers proto :ptr
g_volume_get_activation_root proto :ptr
g_volume_eject_with_operation proto :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_volume_eject_with_operation_finish proto :ptr, :ptr, :ptr
g_volume_get_sort_key proto :ptr

endif

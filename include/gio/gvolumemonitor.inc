ifndef __G_VOLUME_MONITOR_H__
define __G_VOLUME_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_VOLUME_MONITOR         <g_volume_monitor_get_type ()>
G_VOLUME_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_VOLUME_MONITOR, GVolumeMonitor))>
  endm
G_VOLUME_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_VOLUME_MONITOR, GVolumeMonitorClass))>
  endm
G_VOLUME_MONITOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_VOLUME_MONITOR, GVolumeMonitorClass))>
  endm
G_IS_VOLUME_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_VOLUME_MONITOR))>
  endm
G_IS_VOLUME_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_VOLUME_MONITOR))>
  endm


define G_VOLUME_MONITOR_EXTENSION_POINT_NAME <"gio-volume-monitor">


GVolumeMonitor          struct
parent_instance         GObject <>
priv                    gpointer ?
GVolumeMonitor          ends

GVolumeMonitorClass     struct
parent_class            GObjectClass <>
volume_added            proc :ptr, :ptr
volume_removed          proc :ptr, :ptr
volume_changed          proc :ptr, :ptr
mount_added             proc :ptr, :ptr
mount_removed           proc :ptr, :ptr
mount_pre_unmount       proc :ptr, :ptr
mount_changed           proc :ptr, :ptr
drive_connected         proc :ptr, :ptr
drive_disconnected      proc :ptr, :ptr
drive_changed           proc :ptr, :ptr
is_supported            proc
get_connected_drives    proc :ptr
get_volumes             proc :ptr
get_mounts              proc :ptr
get_volume_for_uuid     proc :ptr, :ptr
get_mount_for_uuid      proc :ptr, :ptr
adopt_orphan_mount      proc :ptr, :ptr
drive_eject_button      proc :ptr, :ptr
drive_stop_button       proc :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
GVolumeMonitorClass     ends

g_volume_monitor_get_type proto
g_volume_monitor_get proto
g_volume_monitor_get_connected_drives proto :ptr
g_volume_monitor_get_volumes proto :ptr
g_volume_monitor_get_mounts proto :ptr
g_volume_monitor_get_volume_for_uuid proto :ptr, :ptr
g_volume_monitor_get_mount_for_uuid proto :ptr, :ptr
g_volume_monitor_adopt_orphan_mount proto :ptr

endif

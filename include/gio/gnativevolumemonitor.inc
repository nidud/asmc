ifndef __G_NATIVE_VOLUME_MONITOR_H__
define __G_NATIVE_VOLUME_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gvolumemonitor.inc

define G_TYPE_NATIVE_VOLUME_MONITOR        <g_native_volume_monitor_get_type ()>
G_NATIVE_VOLUME_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NATIVE_VOLUME_MONITOR, GNativeVolumeMonitor))>
  endm
G_NATIVE_VOLUME_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_NATIVE_VOLUME_MONITOR, GNativeVolumeMonitorClass))>
  endm
G_IS_NATIVE_VOLUME_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NATIVE_VOLUME_MONITOR))>
  endm
G_IS_NATIVE_VOLUME_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_NATIVE_VOLUME_MONITOR))>
  endm

define G_NATIVE_VOLUME_MONITOR_EXTENSION_POINT_NAME <"gio-native-volume-monitor">

GNativeVolumeMonitor    struct
parent_instance         GVolumeMonitor <>
GNativeVolumeMonitor    ends

GNativeVolumeMonitorClass struct
parent_class            GVolumeMonitorClass <>
get_mount_for_mount_path proc :ptr, :ptr
GNativeVolumeMonitorClass ends

g_native_volume_monitor_get_type proto

endif

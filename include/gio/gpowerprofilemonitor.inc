ifndef __G_POWER_PROFILE_MONITOR_H__
define __G_POWER_PROFILE_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_POWER_PROFILE_MONITOR_EXTENSION_POINT_NAME <"gio-power-profile-monitor">
define G_TYPE_POWER_PROFILE_MONITOR             <g_power_profile_monitor_get_type>

G_POWER_PROFILE_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_POWER_PROFILE_MONITOR, GPowerProfileMonitor))>
  endm
G_IS_POWER_PROFILE_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_POWER_PROFILE_MONITOR))>
  endm
G_POWER_PROFILE_MONITOR_GET_INTERFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), G_TYPE_POWER_PROFILE_MONITOR, GPowerProfileMonitorInterface))>
  endm

_GPowerProfileMonitorInterface struct
g_iface                 GTypeInterface <>
_GPowerProfileMonitorInterface ends
GPowerProfileMonitorInterface typedef _GPowerProfileMonitorInterface

g_power_profile_monitor_dup_default proto
g_power_profile_monitor_get_power_saver_enabled proto :ptr

endif

ifndef __G_NETWORK_MONITOR_H__
define __G_NETWORK_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_NETWORK_MONITOR_EXTENSION_POINT_NAME <"gio-network-monitor">

define G_TYPE_NETWORK_MONITOR             <g_network_monitor_get_type ()>
G_NETWORK_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NETWORK_MONITOR, GNetworkMonitor))>
  endm
G_IS_NETWORK_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NETWORK_MONITOR))>
  endm
G_NETWORK_MONITOR_GET_INTERFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), G_TYPE_NETWORK_MONITOR, GNetworkMonitorInterface))>
  endm

GNetworkMonitorInterface struct
g_iface                 GTypeInterface <>
network_changed         proc :ptr, :gboolean
can_reach               proc :ptr, :ptr, :ptr, :ptr
can_reach_async         proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
can_reach_finish        proc :ptr, :ptr, :ptr
GNetworkMonitorInterface ends

g_network_monitor_get_type proto
g_network_monitor_get_default proto
g_network_monitor_get_network_available proto :ptr
g_network_monitor_get_network_metered proto :ptr
g_network_monitor_get_connectivity proto :ptr
g_network_monitor_can_reach proto :ptr, :ptr, :ptr, :ptr
g_network_monitor_can_reach_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_network_monitor_can_reach_finish proto :ptr, :ptr, :ptr

endif

ifndef __G_MEMORY_MONITOR_H__
define __G_MEMORY_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_MEMORY_MONITOR_EXTENSION_POINT_NAME <"gio-memory-monitor">

define G_TYPE_MEMORY_MONITOR             <g_memory_monitor_get_type>

G_MEMORY_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_MEMORY_MONITOR, GMemoryMonitor))>
  endm
G_IS_MEMORY_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_MEMORY_MONITOR))>
  endm
G_MEMORY_MONITOR_GET_INTERFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), G_TYPE_MEMORY_MONITOR, GMemoryMonitorInterface))>
  endm

_GMemoryMonitorInterface struct
g_iface                 GTypeInterface <>
low_memory_warning      proc :ptr, :GMemoryMonitorWarningLevel
_GMemoryMonitorInterface ends
GMemoryMonitorInterface typedef _GMemoryMonitorInterface

g_memory_monitor_dup_default proto

endif

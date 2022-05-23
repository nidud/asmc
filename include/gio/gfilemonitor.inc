ifndef __G_FILE_MONITOR_H__
define __G_FILE_MONITOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILE_MONITOR         <g_file_monitor_get_type>
G_FILE_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_MONITOR, GFileMonitor))>
  endm
G_FILE_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_MONITOR, GFileMonitorClass))>
  endm
G_IS_FILE_MONITOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_MONITOR))>
  endm
G_IS_FILE_MONITOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_MONITOR))>
  endm
G_FILE_MONITOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_MONITOR, GFileMonitorClass))>
  endm

;GFileMonitorPrivate     typedef _GFileMonitorPrivate

_GFileMonitor           struct
parent_instance         GObject <>
priv                    ptr GFileMonitorPrivate ?
_GFileMonitor           ends
GFileMonitor            typedef _GFileMonitor

_GFileMonitorClass      struct
parent_class            GObjectClass <>
changed                 proc :ptr, :ptr, :ptr, :GFileMonitorEvent
cancel                  proc :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GFileMonitorClass      ends
GFileMonitorClass       typedef _GFileMonitorClass

g_file_monitor_get_type proto
g_file_monitor_cancel proto :ptr
g_file_monitor_is_cancelled proto :ptr
g_file_monitor_set_rate_limit proto :ptr, :gint
g_file_monitor_emit_event proto :ptr, :ptr, :ptr, :GFileMonitorEvent

endif

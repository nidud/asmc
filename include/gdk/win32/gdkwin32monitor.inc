ifndef __GDK_WIN32_MONITOR_H__
define __GDK_WIN32_MONITOR_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdkmonitor.inc

define GDK_TYPE_WIN32_MONITOR <gdk_win32_monitor_get_type ()>
GDK_WIN32_MONITOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_MONITOR, GdkWin32Monitor))>
  endm
GDK_IS_WIN32_MONITOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_MONITOR))>
  endm

gdk_win32_monitor_get_type proto
gdk_win32_monitor_get_workarea proto :ptr, :ptr

endif

ifndef __GDK_DEVICE_TOOL_H__
define __GDK_DEVICE_TOOL_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkenums.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

define GDK_TYPE_DEVICE_TOOL <gdk_device_tool_get_type ()>
GDK_DEVICE_TOOL macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_DEVICE_TOOL, GdkDeviceTool))>
  endm
GDK_IS_DEVICE_TOOL macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_DEVICE_TOOL))>
  endm

.enum GdkDeviceToolType {
  GDK_DEVICE_TOOL_TYPE_UNKNOWN,
  GDK_DEVICE_TOOL_TYPE_PEN,
  GDK_DEVICE_TOOL_TYPE_ERASER,
  GDK_DEVICE_TOOL_TYPE_BRUSH,
  GDK_DEVICE_TOOL_TYPE_PENCIL,
  GDK_DEVICE_TOOL_TYPE_AIRBRUSH,
  GDK_DEVICE_TOOL_TYPE_MOUSE,
  GDK_DEVICE_TOOL_TYPE_LENS,
}

gdk_device_tool_get_type proto
gdk_device_tool_get_serial proto :ptr
gdk_device_tool_get_hardware_id proto :ptr
gdk_device_tool_get_tool_type proto :ptr
gdk_device_tool_get_axes proto :ptr

endif

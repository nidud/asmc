ifndef __GDK_MONITOR_H__
define __GDK_MONITOR_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdkrectangle.inc
include gdk/gdktypes.inc

define GDK_TYPE_MONITOR <gdk_monitor_get_type ()>
GDK_MONITOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_MONITOR, GdkMonitor))>
  endm
GDK_IS_MONITOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_MONITOR))>
  endm


.enum GdkSubpixelLayout {
  GDK_SUBPIXEL_LAYOUT_UNKNOWN,
  GDK_SUBPIXEL_LAYOUT_NONE,
  GDK_SUBPIXEL_LAYOUT_HORIZONTAL_RGB,
  GDK_SUBPIXEL_LAYOUT_HORIZONTAL_BGR,
  GDK_SUBPIXEL_LAYOUT_VERTICAL_RGB,
  GDK_SUBPIXEL_LAYOUT_VERTICAL_BGR
}

gdk_monitor_get_type proto
gdk_monitor_get_display proto :ptr
gdk_monitor_get_geometry proto :ptr, :ptr
gdk_monitor_get_width_mm proto :ptr
gdk_monitor_get_height_mm proto :ptr
gdk_monitor_get_manufacturer proto :ptr
gdk_monitor_get_model proto :ptr
gdk_monitor_get_connector proto :ptr
gdk_monitor_get_scale_factor proto :ptr
gdk_monitor_get_refresh_rate proto :ptr
gdk_monitor_get_subpixel_layout proto :ptr
gdk_monitor_is_valid proto :ptr

endif

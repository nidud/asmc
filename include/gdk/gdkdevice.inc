ifndef __GDK_DEVICE_H__
define __GDK_DEVICE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkdevicetool.inc
include gdk/gdkenums.inc

define GDK_TYPE_DEVICE         <gdk_device_get_type ()>
GDK_DEVICE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_DEVICE, GdkDevice))>
  endm
GDK_IS_DEVICE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_DEVICE))>
  endm

.enum GdkInputSource {
  GDK_SOURCE_MOUSE,
  GDK_SOURCE_PEN,
  GDK_SOURCE_KEYBOARD,
  GDK_SOURCE_TOUCHSCREEN,
  GDK_SOURCE_TOUCHPAD,
  GDK_SOURCE_TRACKPOINT,
  GDK_SOURCE_TABLET_PAD
}

GdkTimeCoord            struct
time                    guint32 ?
flags                   GdkAxisFlags ?
axes                    real8 GDK_AXIS_LAST dup(?)
GdkTimeCoord            ends

gdk_device_get_type proto

gdk_device_get_name proto :ptr
gdk_device_get_vendor_id proto :ptr
gdk_device_get_product_id proto :ptr
gdk_device_get_display proto :ptr
gdk_device_get_seat proto :ptr
gdk_device_get_device_tool proto :ptr
gdk_device_get_source proto :ptr
gdk_device_get_has_cursor proto :ptr
gdk_device_get_num_touches proto :ptr
gdk_device_get_modifier_state proto :ptr
gdk_device_get_direction proto :ptr
gdk_device_has_bidi_layouts proto :ptr
gdk_device_get_caps_lock_state proto :ptr
gdk_device_get_num_lock_state proto :ptr
gdk_device_get_scroll_lock_state proto :ptr
gdk_device_get_surface_at_position proto :ptr, :ptr, :ptr
gdk_device_get_timestamp proto :ptr

endif

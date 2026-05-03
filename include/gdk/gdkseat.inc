ifndef __GDK_SEAT_H__
define __GDK_SEAT_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdksurface.inc
include gdk/gdkevents.inc
include gdk/gdktypes.inc

define GDK_TYPE_SEAT <gdk_seat_get_type ()>
GDK_SEAT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_SEAT, GdkSeat))>
  endm
GDK_IS_SEAT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_SEAT))>
  endm

.enum GdkSeatCapabilities {
  GDK_SEAT_CAPABILITY_NONE          = 0,
  GDK_SEAT_CAPABILITY_POINTER       = 1 shl 0,
  GDK_SEAT_CAPABILITY_TOUCH         = 1 shl 1,
  GDK_SEAT_CAPABILITY_TABLET_STYLUS = 1 shl 2,
  GDK_SEAT_CAPABILITY_KEYBOARD      = 1 shl 3,
  GDK_SEAT_CAPABILITY_TABLET_PAD    = 1 shl 4,
  GDK_SEAT_CAPABILITY_ALL_POINTING  = (GDK_SEAT_CAPABILITY_POINTER or GDK_SEAT_CAPABILITY_TOUCH or GDK_SEAT_CAPABILITY_TABLET_STYLUS),
  GDK_SEAT_CAPABILITY_ALL           = (GDK_SEAT_CAPABILITY_ALL_POINTING or GDK_SEAT_CAPABILITY_KEYBOARD)
}

GdkSeat                 struct
parent_instance         GObject <>
GdkSeat                 ends

gdk_seat_get_type proto
gdk_seat_get_display proto :ptr
gdk_seat_get_capabilities proto :ptr
gdk_seat_get_devices proto :ptr, :GdkSeatCapabilities
gdk_seat_get_tools proto :ptr
gdk_seat_get_pointer proto :ptr
gdk_seat_get_keyboard proto :ptr

endif

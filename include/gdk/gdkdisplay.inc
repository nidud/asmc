ifndef __GDK_DISPLAY_H__
define __GDK_DISPLAY_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkevents.inc
include gdk/gdkseat.inc
include gdk/gdkmonitor.inc

define GDK_TYPE_DISPLAY              <gdk_display_get_type>
GDK_DISPLAY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DISPLAY, GdkDisplay))>
  endm
GDK_IS_DISPLAY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DISPLAY))>
  endm

gdk_display_get_type proto
gdk_display_open proto :ptr
gdk_display_get_name proto :ptr
gdk_display_device_is_grabbed proto :ptr, :ptr
gdk_display_beep proto :ptr
gdk_display_sync proto :ptr
gdk_display_flush proto :ptr
gdk_display_close proto :ptr
gdk_display_is_closed proto :ptr
gdk_display_is_composited proto :ptr
gdk_display_is_rgba proto :ptr
gdk_display_supports_input_shapes proto :ptr
gdk_display_prepare_gl proto :ptr, :ptr
gdk_display_create_gl_context proto :ptr, :ptr
gdk_display_get_default proto
gdk_display_get_clipboard proto :ptr
gdk_display_get_primary_clipboard proto :ptr
gdk_display_notify_startup_complete proto :ptr, :ptr
gdk_display_get_startup_notification_id proto :ptr
gdk_display_get_app_launch_context proto :ptr
gdk_display_get_default_seat proto :ptr
gdk_display_list_seats proto :ptr
gdk_display_get_monitors proto :ptr
gdk_display_get_monitor_at_surface proto :ptr, :ptr
gdk_display_put_event proto :ptr, :ptr
gdk_display_map_keyval proto :ptr, :guint, :ptr, :ptr
gdk_display_map_keycode proto :ptr, :guint, :ptr, :ptr, :ptr
gdk_display_translate_key proto :ptr, :guint, :GdkModifierType, :sdword, :ptr, :ptr, :ptr, :ptr
gdk_display_get_setting proto :ptr, :ptr, :ptr

endif

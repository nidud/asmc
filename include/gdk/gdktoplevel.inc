ifndef __GDK_TOPLEVEL_H__
define __GDK_TOPLEVEL_H__

if not defined(__GDK_H_INSIDE__) and not defined(GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkseat.inc
include gdk/gdksurface.inc
include gdk/gdktoplevellayout.inc

.enum GdkSurfaceEdge {
  GDK_SURFACE_EDGE_NORTH_WEST,
  GDK_SURFACE_EDGE_NORTH,
  GDK_SURFACE_EDGE_NORTH_EAST,
  GDK_SURFACE_EDGE_WEST,
  GDK_SURFACE_EDGE_EAST,
  GDK_SURFACE_EDGE_SOUTH_WEST,
  GDK_SURFACE_EDGE_SOUTH,
  GDK_SURFACE_EDGE_SOUTH_EAST
}

.enum GdkFullscreenMode {
  GDK_FULLSCREEN_ON_CURRENT_MONITOR,
  GDK_FULLSCREEN_ON_ALL_MONITORS
}

.enum GdkToplevelState {
  GDK_TOPLEVEL_STATE_MINIMIZED        = 1 shl 0,
  GDK_TOPLEVEL_STATE_MAXIMIZED        = 1 shl 1,
  GDK_TOPLEVEL_STATE_STICKY           = 1 shl 2,
  GDK_TOPLEVEL_STATE_FULLSCREEN       = 1 shl 3,
  GDK_TOPLEVEL_STATE_ABOVE            = 1 shl 4,
  GDK_TOPLEVEL_STATE_BELOW            = 1 shl 5,
  GDK_TOPLEVEL_STATE_FOCUSED          = 1 shl 6,
  GDK_TOPLEVEL_STATE_TILED            = 1 shl 7,
  GDK_TOPLEVEL_STATE_TOP_TILED        = 1 shl 8,
  GDK_TOPLEVEL_STATE_TOP_RESIZABLE    = 1 shl 9,
  GDK_TOPLEVEL_STATE_RIGHT_TILED      = 1 shl 10,
  GDK_TOPLEVEL_STATE_RIGHT_RESIZABLE  = 1 shl 11,
  GDK_TOPLEVEL_STATE_BOTTOM_TILED     = 1 shl 12,
  GDK_TOPLEVEL_STATE_BOTTOM_RESIZABLE = 1 shl 13,
  GDK_TOPLEVEL_STATE_LEFT_TILED       = 1 shl 14,
  GDK_TOPLEVEL_STATE_LEFT_RESIZABLE   = 1 shl 15
}

.enum GdkTitlebarGesture {
  GDK_TITLEBAR_GESTURE_DOUBLE_CLICK   = 1,
  GDK_TITLEBAR_GESTURE_RIGHT_CLICK    = 2,
  GDK_TITLEBAR_GESTURE_MIDDLE_CLICK   = 3
}


define GDK_TYPE_TOPLEVEL <gdk_toplevel_get_type ()>

gdk_toplevel_present proto :ptr, :ptr
gdk_toplevel_minimize proto :ptr
gdk_toplevel_lower proto :ptr
gdk_toplevel_focus proto :ptr, :guint32
gdk_toplevel_get_state proto :ptr
gdk_toplevel_set_title proto :ptr, :ptr
gdk_toplevel_set_startup_id proto :ptr, :ptr
gdk_toplevel_set_transient_for proto :ptr, :ptr
gdk_toplevel_set_modal proto :ptr, :gboolean
gdk_toplevel_set_icon_list proto :ptr, :ptr
gdk_toplevel_show_window_menu proto :ptr, :ptr
gdk_toplevel_set_decorated proto :ptr, :gboolean
gdk_toplevel_set_deletable proto :ptr, :gboolean
gdk_toplevel_supports_edge_constraints proto :ptr
gdk_toplevel_inhibit_system_shortcuts proto :ptr, :ptr
gdk_toplevel_restore_system_shortcuts proto :ptr
gdk_toplevel_begin_resize proto :ptr, :GdkSurfaceEdge, :ptr, :sdword, :real8, :real8, :guint32
gdk_toplevel_begin_move proto :ptr, :ptr, :sdword, :real8, :real8, :guint32
gdk_toplevel_titlebar_gesture proto :ptr, :GdkTitlebarGesture

endif

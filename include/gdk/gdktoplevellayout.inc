ifndef __GDK_TOPLEVEL_LAYOUT_H__
define __GDK_TOPLEVEL_LAYOUT_H__

if not defined(__GDK_H_INSIDE__) and not defined(GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkmonitor.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;GdkToplevelLayout       typedef _GdkToplevelLayout

define GDK_TYPE_TOPLEVEL_LAYOUT <gdk_toplevel_layout_get_type ()>

gdk_toplevel_layout_get_type proto
gdk_toplevel_layout_new proto
gdk_toplevel_layout_ref proto :ptr
gdk_toplevel_layout_unref proto :ptr
gdk_toplevel_layout_copy proto :ptr
gdk_toplevel_layout_equal proto :ptr, :ptr
gdk_toplevel_layout_set_maximized proto :ptr, :gboolean
gdk_toplevel_layout_set_fullscreen proto :ptr, :gboolean, :ptr
gdk_toplevel_layout_get_maximized proto :ptr, :ptr
gdk_toplevel_layout_get_fullscreen proto :ptr, :ptr
gdk_toplevel_layout_get_fullscreen_monitor proto :ptr
gdk_toplevel_layout_set_resizable proto :ptr, :gboolean
gdk_toplevel_layout_get_resizable proto :ptr

endif

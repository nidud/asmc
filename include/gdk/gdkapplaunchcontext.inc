ifndef __GDK_APP_LAUNCH_CONTEXT_H__
define __GDK_APP_LAUNCH_CONTEXT_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_APP_LAUNCH_CONTEXT         <gdk_app_launch_context_get_type ()>
GDK_APP_LAUNCH_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_APP_LAUNCH_CONTEXT, GdkAppLaunchContext))>
  endm
GDK_IS_APP_LAUNCH_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_APP_LAUNCH_CONTEXT))>
  endm

gdk_app_launch_context_get_type proto
gdk_app_launch_context_get_display proto :ptr
gdk_app_launch_context_set_desktop proto :ptr, :sdword
gdk_app_launch_context_set_timestamp proto :ptr, :guint32
gdk_app_launch_context_set_icon proto :ptr, :ptr
gdk_app_launch_context_set_icon_name proto :ptr, :ptr

endif

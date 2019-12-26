ifndef __GDK_APP_LAUNCH_CONTEXT_H__
__GDK_APP_LAUNCH_CONTEXT_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gio/gio.inc
include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkscreen.inc

GDK_TYPE_APP_LAUNCH_CONTEXT equ <gdk_app_launch_context_get_type>
GDK_APP_LAUNCH_CONTEXT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_APP_LAUNCH_CONTEXT, GdkAppLaunchContext))>
	endm
GDK_IS_APP_LAUNCH_CONTEXT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_APP_LAUNCH_CONTEXT))>
	endm


;GType
gdk_app_launch_context_get_type proto __cdecl

;GdkAppLaunchContext
gdk_app_launch_context_new proto __cdecl
;void
gdk_app_launch_context_set_display proto __cdecl \
	       context: ptr GdkAppLaunchContext,
	       display: ptr GdkDisplay

;void
gdk_app_launch_context_set_screen proto __cdecl \
	       context: ptr GdkAppLaunchContext,
		screen: ptr GdkScreen

;void
gdk_app_launch_context_set_desktop proto __cdecl \
	       context: ptr GdkAppLaunchContext,
	       desktop: gint

;void
gdk_app_launch_context_set_timestamp proto __cdecl \
	       context: ptr GdkAppLaunchContext,
	     timestamp: guint32

;void
gdk_app_launch_context_set_icon proto __cdecl \
	       context: ptr GdkAppLaunchContext,
		  icon: ptr GIcon

;void
gdk_app_launch_context_set_icon_name proto __cdecl \
	       context: ptr GdkAppLaunchContext,
	     icon_name: ptr char_t

endif

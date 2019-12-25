ifndef __GDK_DISPLAY_H__
__GDK_DISPLAY_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkevents.inc
include gdk/gdkdevicemanager.inc

GDK_TYPE_DISPLAY	equ <gdk_display_get_type>
GDK_DISPLAY macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DISPLAY, GdkDisplay))>
	endm
GDK_IS_DISPLAY macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DISPLAY))>
	endm
ifndef GDK_DISABLE_DEPRECATED
GDK_DISPLAY_OBJECT macro object
	exitm<GDK_DISPLAY(object)>
	endm
endif

;GType
gdk_display_get_type proto __cdecl
;GdkDisplay
gdk_display_open proto __cdecl \
	  display_name: ptr gchar


;const
gdk_display_get_name proto __cdecl \
	       display: ptr GdkDisplay


;gint
gdk_display_get_n_screens proto __cdecl \
	       display: ptr GdkDisplay

;GdkScreen
gdk_display_get_screen proto __cdecl \
	       display: ptr GdkDisplay,
	    screen_num: gint

;GdkScreen
gdk_display_get_default_screen proto __cdecl \
	       display: ptr GdkDisplay


ifndef GDK_MULTIDEVICE_SAFE
;void
gdk_display_pointer_ungrab proto __cdecl \
	       display: ptr GdkDisplay,
		 time_: guint32

;void
gdk_display_keyboard_ungrab proto __cdecl \
	       display: ptr GdkDisplay,
		 time_: guint32

;gboolean
gdk_display_pointer_is_grabbed proto __cdecl \
	       display: ptr GdkDisplay

endif

;gboolean
gdk_display_device_is_grabbed proto __cdecl \
	       display: ptr GdkDisplay,
		device: ptr GdkDevice

;void
gdk_display_beep proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_sync proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_flush proto __cdecl \
	       display: ptr GdkDisplay


;void
gdk_display_close proto __cdecl \
	       display: ptr GdkDisplay

;gboolean
gdk_display_is_closed proto __cdecl \
	       display: ptr GdkDisplay


;GList
gdk_display_list_devices proto __cdecl \
	       display: ptr GdkDisplay


;GdkEvent*
gdk_display_get_event proto __cdecl \
	       display: ptr GdkDisplay

;GdkEvent*
gdk_display_peek_event proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_put_event proto __cdecl \
	       display: ptr GdkDisplay,
		 event: ptr GdkEvent

;gboolean
gdk_display_has_pending proto __cdecl \
	       display: ptr GdkDisplay


;void
gdk_display_set_double_click_time proto __cdecl \
	       display: ptr GdkDisplay,
		  msec: guint

;void
gdk_display_set_double_click_distance proto __cdecl \
	       display: ptr GdkDisplay,
	      distance: guint


;GdkDisplay
gdk_display_get_default proto __cdecl

ifndef GDK_MULTIDEVICE_SAFE
;void
gdk_display_get_pointer proto __cdecl \
	       display: ptr GdkDisplay,
		screen: ptr GdkScreen,
		     x: ptr gint,
		     y: ptr gint,
		  mask: ptr GdkModifierType

;GdkWindow
gdk_display_get_window_at_pointer proto __cdecl \
	       display: ptr GdkDisplay,
		 win_x: ptr gint,
		 win_y: ptr gint

;void
gdk_display_warp_pointer proto __cdecl \
	       display: ptr GdkDisplay,
		screen: ptr GdkScreen,
		     x: gint,
		     y: gint

endif

;GdkDisplay
gdk_display_open_default_libgtk_only proto __cdecl

;gboolean
gdk_display_supports_cursor_alpha proto __cdecl \
	       display: ptr GdkDisplay

;gboolean
gdk_display_supports_cursor_color proto __cdecl \
	       display: ptr GdkDisplay

;guint
gdk_display_get_default_cursor_size proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_get_maximal_cursor_size proto __cdecl \
	       display: ptr GdkDisplay,
		 width: ptr guint,
		height: ptr guint


;GdkWindow
gdk_display_get_default_group proto __cdecl \
	       display: ptr GdkDisplay


;gboolean
gdk_display_supports_selection_notification proto __cdecl \
	       display: ptr GdkDisplay

;gboolean
gdk_display_request_selection_notification proto __cdecl \
	       display: ptr GdkDisplay,
	     selection: GdkAtom


;gboolean
gdk_display_supports_clipboard_persistence proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_store_clipboard proto __cdecl \
	       display: ptr GdkDisplay,
      clipboard_window: ptr GdkWindow,
		 time_: guint32,
	       targets: ptr GdkAtom,
	     n_targets: gint


;gboolean
gdk_display_supports_shapes proto __cdecl \
	       display: ptr GdkDisplay

;gboolean
gdk_display_supports_input_shapes proto __cdecl \
	       display: ptr GdkDisplay

;gboolean
gdk_display_supports_composite proto __cdecl \
	       display: ptr GdkDisplay

;void
gdk_display_notify_startup_complete proto __cdecl \
	       display: ptr GdkDisplay,
	    startup_id: ptr gchar


;GdkDeviceManager
gdk_display_get_device_manager proto __cdecl \
	       display: ptr GdkDisplay


;GdkAppLaunchContext
gdk_display_get_app_launch_context proto __cdecl \
	       display: ptr GdkDisplay

endif

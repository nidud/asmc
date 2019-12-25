ifndef __GDK_SCREEN_H__
__GDK_SCREEN_H__ equ 1
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

;include cairo.inc
include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkdisplay.inc

GDK_TYPE_SCREEN		equ <gdk_screen_get_type>
GDK_SCREEN macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_SCREEN, GdkScreen))>
	endm
GDK_IS_SCREEN macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_SCREEN))>
	endm

;GType
gdk_screen_get_type proto __cdecl

;GdkVisual
gdk_screen_get_system_visual proto __cdecl \
		screen: ptr GdkScreen

;GdkVisual
gdk_screen_get_rgba_visual proto __cdecl \
		screen: ptr GdkScreen

;gboolean
gdk_screen_is_composited proto __cdecl \
		screen: ptr GdkScreen


;GdkWindow
gdk_screen_get_root_window proto __cdecl \
		screen: ptr GdkScreen

;GdkDisplay
gdk_screen_get_display proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_number proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_width proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_height proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_width_mm proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_height_mm proto __cdecl \
		screen: ptr GdkScreen


;GList
gdk_screen_list_visuals proto __cdecl \
		screen: ptr GdkScreen

;GList
gdk_screen_get_toplevel_windows proto __cdecl \
		screen: ptr GdkScreen

;gchar
gdk_screen_make_display_name proto __cdecl \
		screen: ptr GdkScreen


;gint
gdk_screen_get_n_monitors proto __cdecl \
		screen: ptr GdkScreen

;gint
gdk_screen_get_primary_monitor proto __cdecl \
		screen: ptr GdkScreen

;void
gdk_screen_get_monitor_geometry proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint,
		  dest: ptr GdkRectangle

;void
gdk_screen_get_monitor_workarea proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint,
		  dest: ptr GdkRectangle


;gint
gdk_screen_get_monitor_at_point proto __cdecl \
		screen: ptr GdkScreen,
		     x: gint,
		     y: gint

;gint
gdk_screen_get_monitor_at_window proto __cdecl \
		screen: ptr GdkScreen,
		window: ptr GdkWindow

;gint
gdk_screen_get_monitor_width_mm proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint

;gint
gdk_screen_get_monitor_height_mm proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint

;gchar
gdk_screen_get_monitor_plug_name proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint

;gint
gdk_screen_get_monitor_scale_factor proto __cdecl \
		screen: ptr GdkScreen,
	   monitor_num: gint


;GdkScreen
gdk_screen_get_default proto __cdecl

;gboolean
gdk_screen_get_setting proto __cdecl \
		screen: ptr GdkScreen,
		  name: ptr gchar,
		 value: ptr GValue


;void
gdk_screen_set_font_options proto __cdecl \
		screen: ptr GdkScreen,
	       options: ptr cairo_font_options_t

;const
gdk_screen_get_font_options proto __cdecl \
		screen: ptr GdkScreen


;void
gdk_screen_set_resolution proto __cdecl \
		screen: ptr GdkScreen,
		   dpi: gdouble

;gdouble
gdk_screen_get_resolution proto __cdecl \
		screen: ptr GdkScreen


;GdkWindow
gdk_screen_get_active_window proto __cdecl \
		screen: ptr GdkScreen

;GList
gdk_screen_get_window_stack proto __cdecl \
		screen: ptr GdkScreen

endif

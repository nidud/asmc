ifndef __GDK_DEVICE_H__
__GDK_DEVICE_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

GDK_TYPE_DEVICE		equ <gdk_device_get_type>
GDK_DEVICE macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_DEVICE, GdkDevice))>
	endm
GDK_IS_DEVICE macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_DEVICE))>
	endm

.enum GdkInputSource {
  GDK_SOURCE_MOUSE,
  GDK_SOURCE_PEN,
  GDK_SOURCE_ERASER,
  GDK_SOURCE_CURSOR,
  GDK_SOURCE_KEYBOARD,
  GDK_SOURCE_TOUCHSCREEN,
  GDK_SOURCE_TOUCHPAD
}

.enum GdkInputMode {
  GDK_MODE_DISABLED,
  GDK_MODE_SCREEN,
  GDK_MODE_WINDOW
}

.enum GdkAxisUse {
  GDK_AXIS_IGNORE,
  GDK_AXIS_X,
  GDK_AXIS_Y,
  GDK_AXIS_PRESSURE,
  GDK_AXIS_XTILT,
  GDK_AXIS_YTILT,
  GDK_AXIS_WHEEL,
  GDK_AXIS_LAST
}

.enum GdkDeviceType {
  GDK_DEVICE_TYPE_MASTER,
  GDK_DEVICE_TYPE_SLAVE,
  GDK_DEVICE_TYPE_FLOATING
}

GDK_MAX_TIMECOORD_AXES	equ 128

GdkTimeCoord		STRUC
time			guint32 ?
axes			gdouble GDK_MAX_TIMECOORD_AXES dup(?)
GdkTimeCoord		ENDS

;GType
gdk_device_get_type proto __cdecl

;const
gdk_device_get_name proto __cdecl \
		device: ptr GdkDevice

;gboolean
gdk_device_get_has_cursor proto __cdecl \
		device: ptr GdkDevice


;GdkInputSource
gdk_device_get_source proto __cdecl \
		device: ptr GdkDevice


;GdkInputMode
gdk_device_get_mode proto __cdecl \
		device: ptr GdkDevice

;gboolean
gdk_device_set_mode proto __cdecl \
		device: ptr GdkDevice,
		  mode: GdkInputMode


;gint
gdk_device_get_n_keys proto __cdecl \
		device: ptr GdkDevice

;gboolean
gdk_device_get_key proto __cdecl \
		device: ptr GdkDevice,
		index_: guint,
		keyval: ptr guint,
	     modifiers: ptr GdkModifierType

;void
gdk_device_set_key proto __cdecl \
		device: ptr GdkDevice,
		index_: guint,
		keyval: guint,
	     modifiers: GdkModifierType


;GdkAxisUse
gdk_device_get_axis_use proto __cdecl \
		device: ptr GdkDevice,
		index_: guint

;void
gdk_device_set_axis_use proto __cdecl \
		device: ptr GdkDevice,
		index_: guint,
		   use: GdkAxisUse



;void
gdk_device_get_state proto __cdecl \
		device: ptr GdkDevice,
		window: ptr GdkWindow,
		  axes: ptr gdouble,
		  mask: ptr GdkModifierType

;void
gdk_device_get_position proto __cdecl \
		device: ptr GdkDevice,
		screen: ptr GdkScreen,
		     x: ptr gint,
		     y: ptr gint

;GdkWindow
gdk_device_get_window_at_position proto __cdecl \
		device: ptr GdkDevice,
		 win_x: ptr gint,
		 win_y: ptr gint

;void
gdk_device_get_position_double proto __cdecl \
		device: ptr GdkDevice,
		screen: ptr GdkScreen,
		     x: ptr gdouble,
		     y: ptr gdouble

;GdkWindow
gdk_device_get_window_at_position_double proto __cdecl \
		device: ptr GdkDevice,
		 win_x: ptr gdouble,
		 win_y: ptr gdouble

;gboolean
gdk_device_get_history proto __cdecl \
		device: ptr GdkDevice,
		window: ptr GdkWindow,
		 start: guint32,
		  stop: guint32,
		events: ptr GdkTimeCoord,
	      n_events: ptr gint

;void
gdk_device_free_history proto __cdecl \
		events: ptr GdkTimeCoord,
	      n_events: gint


;gint
gdk_device_get_n_axes proto __cdecl \
		device: ptr GdkDevice

;GList
gdk_device_list_axes proto __cdecl \
		device: ptr GdkDevice

;gboolean
gdk_device_get_axis_value proto __cdecl \
		device: ptr GdkDevice,
		  axes: ptr gdouble,
	    axis_label: GdkAtom,
		 value: ptr gdouble


;gboolean
gdk_device_get_axis proto __cdecl \
		device: ptr GdkDevice,
		  axes: ptr gdouble,
		   use: GdkAxisUse,
		 value: ptr gdouble

;GdkDisplay
gdk_device_get_display proto __cdecl \
		device: ptr GdkDevice


;GdkDevice
gdk_device_get_associated_device proto __cdecl \
		device: ptr GdkDevice

;GList
gdk_device_list_slave_devices proto __cdecl \
		device: ptr GdkDevice


;GdkDeviceType
gdk_device_get_device_type proto __cdecl \
		device: ptr GdkDevice


;GdkGrabStatus
gdk_device_grab proto __cdecl \
		device: ptr GdkDevice,
		window: ptr GdkWindow,
	grab_ownership: GdkGrabOwnership,
	  owner_events: gboolean,
	    event_mask: GdkEventMask,
		cursor: ptr GdkCursor,
		 time_: guint32


;void
gdk_device_ungrab proto __cdecl \
		device: ptr GdkDevice,
		 time_: guint32


;void
gdk_device_warp proto __cdecl \
		device: ptr GdkDevice,
		screen: ptr GdkScreen,
		     x: gint,
		     y: gint


;gboolean
gdk_device_grab_info_libgtk_only proto __cdecl \
	       display: ptr GdkDisplay,
		device: ptr GdkDevice,
	   grab_window: ptr GdkWindow,
	  owner_events: ptr gboolean


;GdkWindow
gdk_device_get_last_event_window proto __cdecl \
		device: ptr GdkDevice


;const
gdk_device_get_vendor_id proto __cdecl \
		device: ptr GdkDevice

;const
gdk_device_get_product_id proto __cdecl \
		device: ptr GdkDevice

endif

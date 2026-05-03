ifndef __GDK_EVENTS_H__
define __GDK_EVENTS_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkdevice.inc
include gdk/gdkdevicetool.inc
include gdk/gdkdrag.inc
include gdk/gdkenums.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

define GDK_TYPE_EVENT	<gdk_event_get_type ()>
define GDK_TYPE_EVENT_SEQUENCE <gdk_event_sequence_get_type ()>

GDK_IS_EVENT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_EVENT))>
  endm
GDK_EVENT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_EVENT, GdkEvent))>
  endm

GDK_IS_EVENT_TYPE macro event, type
  exitm<gdk_event_get_event_type(vent)) == (type))>
  endm

define GDK_PRIORITY_EVENTS     (G_PRIORITY_DEFAULT)
define GDK_PRIORITY_REDRAW     (G_PRIORITY_HIGH_IDLE + 20)
define GDK_EVENT_PROPAGATE     (FALSE)
define GDK_EVENT_STOP	       (TRUE)
define GDK_BUTTON_PRIMARY      (1)
define GDK_BUTTON_MIDDLE       (2)
define GDK_BUTTON_SECONDARY    (3)

define GDK_TYPE_BUTTON_EVENT <gdk_button_event_get_type ()>
define GDK_TYPE_CROSSING_EVENT <gdk_crossing_event_get_type ()>
define GDK_TYPE_DELETE_EVENT <gdk_delete_event_get_type ()>
define GDK_TYPE_DND_EVENT <gdk_dnd_event_get_type ()>
define GDK_TYPE_FOCUS_EVENT <gdk_focus_event_get_type ()>
define GDK_TYPE_GRAB_BROKEN_EVENT <gdk_grab_broken_event_get_type ()>
define GDK_TYPE_KEY_EVENT <gdk_key_event_get_type ()>
define GDK_TYPE_MOTION_EVENT <gdk_motion_event_get_type ()>
define GDK_TYPE_PAD_EVENT <gdk_pad_event_get_type ()>
define GDK_TYPE_PROXIMITY_EVENT <gdk_proximity_event_get_type ()>
define GDK_TYPE_SCROLL_EVENT <gdk_scroll_event_get_type ()>
define GDK_TYPE_TOUCH_EVENT <gdk_touch_event_get_type ()>
define GDK_TYPE_TOUCHPAD_EVENT <gdk_touchpad_event_get_type ()>

.enum GdkEventType {
  GDK_DELETE,
  GDK_MOTION_NOTIFY,
  GDK_BUTTON_PRESS,
  GDK_BUTTON_RELEASE,
  GDK_KEY_PRESS,
  GDK_KEY_RELEASE,
  GDK_ENTER_NOTIFY,
  GDK_LEAVE_NOTIFY,
  GDK_FOCUS_CHANGE,
  GDK_PROXIMITY_IN,
  GDK_PROXIMITY_OUT,
  GDK_DRAG_ENTER,
  GDK_DRAG_LEAVE,
  GDK_DRAG_MOTION,
  GDK_DROP_START,
  GDK_SCROLL,
  GDK_GRAB_BROKEN,
  GDK_TOUCH_BEGIN,
  GDK_TOUCH_UPDATE,
  GDK_TOUCH_END,
  GDK_TOUCH_CANCEL,
  GDK_TOUCHPAD_SWIPE,
  GDK_TOUCHPAD_PINCH,
  GDK_PAD_BUTTON_PRESS,
  GDK_PAD_BUTTON_RELEASE,
  GDK_PAD_RING,
  GDK_PAD_STRIP,
  GDK_PAD_GROUP_MODE,
  GDK_TOUCHPAD_HOLD,
  GDK_EVENT_LAST
}


.enum GdkTouchpadGesturePhase {
  GDK_TOUCHPAD_GESTURE_PHASE_BEGIN,
  GDK_TOUCHPAD_GESTURE_PHASE_UPDATE,
  GDK_TOUCHPAD_GESTURE_PHASE_END,
  GDK_TOUCHPAD_GESTURE_PHASE_CANCEL
}


.enum GdkScrollDirection {
  GDK_SCROLL_UP,
  GDK_SCROLL_DOWN,
  GDK_SCROLL_LEFT,
  GDK_SCROLL_RIGHT,
  GDK_SCROLL_SMOOTH
}


.enum GdkNotifyType {
  GDK_NOTIFY_ANCESTOR		= 0,
  GDK_NOTIFY_VIRTUAL		= 1,
  GDK_NOTIFY_INFERIOR		= 2,
  GDK_NOTIFY_NONLINEAR		= 3,
  GDK_NOTIFY_NONLINEAR_VIRTUAL	= 4,
  GDK_NOTIFY_UNKNOWN		= 5
}


.enum GdkCrossingMode {
  GDK_CROSSING_NORMAL,
  GDK_CROSSING_GRAB,
  GDK_CROSSING_UNGRAB,
  GDK_CROSSING_GTK_GRAB,
  GDK_CROSSING_GTK_UNGRAB,
  GDK_CROSSING_STATE_CHANGED,
  GDK_CROSSING_TOUCH_BEGIN,
  GDK_CROSSING_TOUCH_END,
  GDK_CROSSING_DEVICE_SWITCH
}

gdk_event_get_type proto
gdk_event_sequence_get_type proto
gdk_event_ref proto :ptr
gdk_event_unref proto :ptr
gdk_event_get_event_type proto :ptr
gdk_event_get_surface proto :ptr
gdk_event_get_seat proto :ptr
gdk_event_get_device proto :ptr
gdk_event_get_device_tool proto :ptr
gdk_event_get_time proto :ptr
gdk_event_get_display proto :ptr
gdk_event_get_event_sequence proto :ptr
gdk_event_get_modifier_state proto :ptr
gdk_event_get_position proto :ptr, :ptr, :ptr
gdk_event_get_axes proto :ptr, :ptr, :ptr
gdk_event_get_axis proto :ptr, :GdkAxisUse, :ptr
gdk_event_get_history proto :ptr, :ptr
gdk_event_get_pointer_emulated proto :ptr

gdk_button_event_get_type proto
gdk_button_event_get_button proto :ptr
gdk_scroll_event_get_type proto
gdk_scroll_event_get_direction proto :ptr
gdk_scroll_event_get_deltas proto :ptr, :ptr, :ptr

gdk_scroll_event_is_stop proto :ptr
gdk_key_event_get_type proto
gdk_key_event_get_keyval proto :ptr
gdk_key_event_get_keycode proto :ptr
gdk_key_event_get_consumed_modifiers proto :ptr
gdk_key_event_get_layout proto :ptr
gdk_key_event_get_level proto :ptr
gdk_key_event_is_modifier proto :ptr
gdk_focus_event_get_type proto
gdk_focus_event_get_in proto :ptr
gdk_touch_event_get_type proto
gdk_touch_event_get_emulating_pointer proto :ptr
gdk_crossing_event_get_type proto
gdk_crossing_event_get_mode proto :ptr
gdk_crossing_event_get_detail proto :ptr
gdk_crossing_event_get_focus proto :ptr
gdk_touchpad_event_get_type proto
gdk_touchpad_event_get_gesture_phase proto :ptr
gdk_touchpad_event_get_n_fingers proto :ptr
gdk_touchpad_event_get_deltas proto :ptr, :ptr, :ptr
gdk_touchpad_event_get_pinch_angle_delta proto :ptr
gdk_touchpad_event_get_pinch_scale proto :ptr
gdk_pad_event_get_type proto
gdk_pad_event_get_button proto :ptr
gdk_pad_event_get_axis_value proto :ptr, :ptr, :ptr
gdk_pad_event_get_group_mode proto :ptr, :ptr, :ptr
gdk_dnd_event_get_type proto
gdk_dnd_event_get_drop proto :ptr
gdk_grab_broken_event_get_type proto
gdk_grab_broken_event_get_grab_surface proto :ptr
gdk_grab_broken_event_get_implicit proto :ptr
gdk_motion_event_get_type proto
gdk_delete_event_get_type proto
gdk_proximity_event_get_type proto
gdk_event_triggers_context_menu proto :ptr
gdk_events_get_distance proto :ptr, :ptr, :ptr
gdk_events_get_angle proto :ptr, :ptr, :ptr
gdk_events_get_center proto :ptr, :ptr, :ptr, :ptr


.enum GdkKeyMatch {
  GDK_KEY_MATCH_NONE,
  GDK_KEY_MATCH_PARTIAL,
  GDK_KEY_MATCH_EXACT
}

gdk_key_event_matches proto :ptr, :guint, :GdkModifierType
gdk_key_event_get_match proto :ptr, :ptr, :ptr

endif

ifndef __GDK_EVENTS_H__
__GDK_EVENTS_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkdnd.inc
include gdk/gdkdevice.inc

GDK_TYPE_EVENT		equ <gdk_event_get_type>
GDK_TYPE_EVENT_SEQUENCE equ <gdk_event_sequence_get_type>

GDK_PRIORITY_EVENTS	equ (G_PRIORITY_DEFAULT)
GDK_PRIORITY_REDRAW	equ (G_PRIORITY_HIGH_IDLE + 20)
GDK_EVENT_PROPAGATE	equ (FALSE)
GDK_EVENT_STOP		equ (TRUE)
GDK_BUTTON_PRIMARY	equ (1)
GDK_BUTTON_MIDDLE	equ (2)
GDK_BUTTON_SECONDARY	equ (3)

CALLBACKC(GdkEventFunc, :ptr GdkEvent, :gpointer)

GdkXEvent		equ <>

.enum GdkFilterReturn {
  GDK_FILTER_CONTINUE,
  GDK_FILTER_TRANSLATE,
  GDK_FILTER_REMOVE
}

CALLBACKC(GdkFilterFunc, :ptr GdkXEvent, :ptr GdkEvent, :gpointer)

.enum GdkEventType {
  GDK_NOTHING		= -1,
  GDK_DELETE		= 0,
  GDK_DESTROY		= 1,
  GDK_EXPOSE		= 2,
  GDK_MOTION_NOTIFY	= 3,
  GDK_BUTTON_PRESS	= 4,
  GDK_2BUTTON_PRESS	= 5,
  GDK_DOUBLE_BUTTON_PRESS = GDK_2BUTTON_PRESS,
  GDK_3BUTTON_PRESS	= 6,
  GDK_TRIPLE_BUTTON_PRESS = GDK_3BUTTON_PRESS,
  GDK_BUTTON_RELEASE	= 7,
  GDK_KEY_PRESS		= 8,
  GDK_KEY_RELEASE	= 9,
  GDK_ENTER_NOTIFY	= 10,
  GDK_LEAVE_NOTIFY	= 11,
  GDK_FOCUS_CHANGE	= 12,
  GDK_CONFIGURE		= 13,
  GDK_MAP		= 14,
  GDK_UNMAP		= 15,
  GDK_PROPERTY_NOTIFY	= 16,
  GDK_SELECTION_CLEAR	= 17,
  GDK_SELECTION_REQUEST = 18,
  GDK_SELECTION_NOTIFY	= 19,
  GDK_PROXIMITY_IN	= 20,
  GDK_PROXIMITY_OUT	= 21,
  GDK_DRAG_ENTER	= 22,
  GDK_DRAG_LEAVE	= 23,
  GDK_DRAG_MOTION	= 24,
  GDK_DRAG_STATUS	= 25,
  GDK_DROP_START	= 26,
  GDK_DROP_FINISHED	= 27,
  GDK_CLIENT_EVENT	= 28,
  GDK_VISIBILITY_NOTIFY = 29,
  GDK_SCROLL		= 31,
  GDK_WINDOW_STATE	= 32,
  GDK_SETTING		= 33,
  GDK_OWNER_CHANGE	= 34,
  GDK_GRAB_BROKEN	= 35,
  GDK_DAMAGE		= 36,
  GDK_TOUCH_BEGIN	= 37,
  GDK_TOUCH_UPDATE	= 38,
  GDK_TOUCH_END		= 39,
  GDK_TOUCH_CANCEL	= 40,
  GDK_TOUCHPAD_SWIPE	= 41,
  GDK_TOUCHPAD_PINCH	= 42,
  GDK_EVENT_LAST
}

.enum GdkVisibilityState {
  GDK_VISIBILITY_UNOBSCURED,
  GDK_VISIBILITY_PARTIAL,
  GDK_VISIBILITY_FULLY_OBSCURED
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

.enum GdkPropertyState {
  GDK_PROPERTY_NEW_VALUE,
  GDK_PROPERTY_DELETE
}

.enum GdkWindowState {
  GDK_WINDOW_STATE_WITHDRAWN  = 1 shl 0,
  GDK_WINDOW_STATE_ICONIFIED  = 1 shl 1,
  GDK_WINDOW_STATE_MAXIMIZED  = 1 shl 2,
  GDK_WINDOW_STATE_STICKY     = 1 shl 3,
  GDK_WINDOW_STATE_FULLSCREEN = 1 shl 4,
  GDK_WINDOW_STATE_ABOVE      = 1 shl 5,
  GDK_WINDOW_STATE_BELOW      = 1 shl 6,
  GDK_WINDOW_STATE_FOCUSED    = 1 shl 7,
  GDK_WINDOW_STATE_TILED      = 1 shl 8
}

.enum GdkSettingAction {
  GDK_SETTING_ACTION_NEW,
  GDK_SETTING_ACTION_CHANGED,
  GDK_SETTING_ACTION_DELETED
}

.enum GdkOwnerChange {
  GDK_OWNER_CHANGE_NEW_OWNER,
  GDK_OWNER_CHANGE_DESTROY,
  GDK_OWNER_CHANGE_CLOSE
}

GdkEventAny		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
GdkEventAny		ENDS

GdkEventExpose		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
area			GdkRectangle <>
region			ptr_t ?
count			gint ?
GdkEventExpose		ENDS

GdkEventVisibility	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
state			GdkVisibilityState ?
GdkEventVisibility	ENDS

GdkEventMotion		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
axes			ptr_t ?
state			guint ?
is_hint			gint16 ?
device			ptr_t ?
x_root			gdouble ?
y_root			gdouble ?
GdkEventMotion		ENDS

GdkEventButton		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
axes			ptr_t ?
state			guint ?
button			guint ?
device			ptr_t ?
x_root			gdouble ?
y_root			gdouble ?
GdkEventButton		ENDS

GdkEventTouch		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
axes			ptr_t ?
state			guint ?
sequence		ptr_t ?
emulating_pointer	gboolean ?
device			ptr_t ?
x_root			gdouble ?
y_root			gdouble ?
GdkEventTouch		ENDS

GdkEventScroll		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
state			guint ?
direction		GdkScrollDirection ?
device			ptr_t ?
x_root			gdouble ?
y_root			gdouble ?
delta_x			gdouble ?
delta_y			gdouble ?
GdkEventScroll		ENDS

GdkEventKey		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
state			guint ?
keyval			guint ?
length			gint ?
string			ptr_t ?
hardware_keycode	guint16 ?
_group			guint8 ?
is_modifier		guint ? ; : 1
GdkEventKey		ENDS

GdkEventCrossing	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
subwindow		ptr_t ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
x_root			gdouble ?
y_root			gdouble ?
mode			GdkCrossingMode ?
detail			GdkNotifyType ?
focus			gboolean ?
state			guint ?
GdkEventCrossing	ENDS

GdkEventFocus		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
_in			gint16 ?
GdkEventFocus		ENDS

GdkEventConfigure	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
x			gint ?
y			gint ?
width			gint ?
height			gint ?
GdkEventConfigure	ENDS

GdkEventProperty	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
atom			GdkAtom ?
time			guint32 ?
state			guint ?
GdkEventProperty	ENDS

GdkEventSelection	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
selection		GdkAtom ?
target			GdkAtom ?
property		GdkAtom ?
time			guint32 ?
requestor		ptr_t ?
GdkEventSelection	ENDS

GdkEventOwnerChange	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
owner			ptr_t ?
reason			GdkOwnerChange ?
selection		GdkAtom ?
time			guint32 ?
selection_time		guint32 ?
GdkEventOwnerChange	ENDS

GdkEventProximity	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
time			guint32 ?
device			ptr_t ?
GdkEventProximity	ENDS

GdkEventSetting		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
action			GdkSettingAction ?
name			ptr_t ?
GdkEventSetting		ENDS

GdkEventWindowState	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
changed_mask		GdkWindowState ?
new_window_state	GdkWindowState ?
GdkEventWindowState	ENDS

GdkEventGrabBroken	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
keyboard		gboolean ?
implicit		gboolean ?
grab_window		ptr_t ?
GdkEventGrabBroken	ENDS

GdkEventDND		STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
context			ptr_t ?
time			guint32 ?
x_root			gshort ?
y_root			gshort ?
GdkEventDND		ENDS

GdkEventTouchpadSwipe	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
phase			gint8 ?
n_fingers		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
_dx			gdouble ?
dy			gdouble ?
x_root			gdouble ?
y_root			gdouble ?
state			guint ?
GdkEventTouchpadSwipe	ENDS

GdkEventTouchpadPinch	STRUC
type			GdkEventType ?
window			ptr_t ?
send_event		gint8 ?
phase			gint8 ?
n_fingers		gint8 ?
time			guint32 ?
x			gdouble ?
y			gdouble ?
_dx			gdouble ?
dy			gdouble ?
angle_delta		gdouble ?
scale			gdouble ?
x_root			gdouble ?
y_root			gdouble ?
state			guint ?
GdkEventTouchpadPinch	ENDS

GdkEvent		UNION
type			GdkEventType ?
any			GdkEventAny <>
expose			GdkEventExpose <>
visibility		GdkEventVisibility <>
motion			GdkEventMotion <>
button			GdkEventButton <>
touch			GdkEventTouch <>
scroll			GdkEventScroll <>
key			GdkEventKey <>
crossing		GdkEventCrossing <>
focus_change		GdkEventFocus <>
configure		GdkEventConfigure <>
property		GdkEventProperty <>
selection		GdkEventSelection <>
owner_change		GdkEventOwnerChange <>
proximity		GdkEventProximity <>
dnd			GdkEventDND <>
window_state		GdkEventWindowState <>
setting			GdkEventSetting <>
grab_broken		GdkEventGrabBroken <>
touchpad_swipe		GdkEventTouchpadSwipe <>
touchpad_pinch		GdkEventTouchpadPinch <>
GdkEvent		ENDS


;GType
gdk_event_get_type proto __cdecl

;GType
gdk_event_sequence_get_type proto __cdecl

;gboolean
gdk_events_pending proto __cdecl
;GdkEvent*
gdk_event_get proto __cdecl

;GdkEvent*
gdk_event_peek proto __cdecl
;void
gdk_event_put proto __cdecl \
		 event: ptr GdkEvent


;GdkEvent*
gdk_event_new proto __cdecl \
		  type: GdkEventType

;GdkEvent*
gdk_event_copy proto __cdecl \
		 event: ptr GdkEvent

;void
gdk_event_free proto __cdecl \
		 event: ptr GdkEvent


;GdkWindow
gdk_event_get_window proto __cdecl \
		 event: ptr GdkEvent


;guint32
gdk_event_get_time proto __cdecl \
		 event: ptr GdkEvent

;gboolean
gdk_event_get_state proto __cdecl \
		 event: ptr GdkEvent,
		 state: ptr GdkModifierType

;gboolean
gdk_event_get_coords proto __cdecl \
		 event: ptr GdkEvent,
		 x_win: ptr gdouble,
		 y_win: ptr gdouble

;gboolean
gdk_event_get_root_coords proto __cdecl \
		 event: ptr GdkEvent,
		x_root: ptr gdouble,
		y_root: ptr gdouble

;gboolean
gdk_event_get_button proto __cdecl \
		 event: ptr GdkEvent,
		button: ptr guint

;gboolean
gdk_event_get_click_count proto __cdecl \
		 event: ptr GdkEvent,
	   click_count: ptr guint

;gboolean
gdk_event_get_keyval proto __cdecl \
		 event: ptr GdkEvent,
		keyval: ptr guint

;gboolean
gdk_event_get_keycode proto __cdecl \
		 event: ptr GdkEvent,
	       keycode: ptr guint16

;gboolean
gdk_event_get_scroll_direction proto __cdecl \
		 event: ptr GdkEvent,
	     direction: ptr GdkScrollDirection

;gboolean
gdk_event_get_scroll_deltas proto __cdecl \
		 event: ptr GdkEvent,
	       delta_x: ptr gdouble,
	       delta_y: ptr gdouble


;gboolean
gdk_event_get_axis proto __cdecl \
		 event: ptr GdkEvent,
	      axis_use: GdkAxisUse,
		 value: ptr gdouble

;void
gdk_event_set_device proto __cdecl \
		 event: ptr GdkEvent,
		device: ptr GdkDevice

;GdkDevice*
gdk_event_get_device proto __cdecl \
		 event: ptr GdkEvent

;void
gdk_event_set_source_device proto __cdecl \
		 event: ptr GdkEvent,
		device: ptr GdkDevice

;GdkDevice*
gdk_event_get_source_device proto __cdecl \
		 event: ptr GdkEvent

;void
gdk_event_request_motions proto __cdecl \
		 event: ptr GdkEventMotion

;gboolean
gdk_event_triggers_context_menu proto __cdecl \
		 event: ptr GdkEvent


;gboolean
gdk_events_get_distance proto __cdecl \
		event1: ptr GdkEvent,
		event2: ptr GdkEvent,
	      distance: ptr gdouble

;gboolean
gdk_events_get_angle proto __cdecl \
		event1: ptr GdkEvent,
		event2: ptr GdkEvent,
		 angle: ptr gdouble

;gboolean
gdk_events_get_center proto __cdecl \
		event1: ptr GdkEvent,
		event2: ptr GdkEvent,
		     x: ptr gdouble,
		     y: ptr gdouble


;void
gdk_event_handler_set proto __cdecl \
		  func: GdkEventFunc,
		  data: gpointer,
		notify: GDestroyNotify


;void
gdk_event_set_screen proto __cdecl \
		 event: ptr GdkEvent,
		screen: ptr GdkScreen

;GdkScreen
gdk_event_get_screen proto __cdecl \
		 event: ptr GdkEvent


;GdkEventSequence
gdk_event_get_event_sequence proto __cdecl \
		 event: ptr GdkEvent


;GdkEventType
gdk_event_get_event_type proto __cdecl \
		 event: ptr GdkEvent


;void
gdk_set_show_events proto __cdecl \
	   show_events: gboolean

;gboolean
gdk_get_show_events proto __cdecl

;gboolean
gdk_setting_get proto __cdecl \
		  name: ptr gchar,
		 value: ptr GValue

endif

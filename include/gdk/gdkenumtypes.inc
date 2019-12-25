ifndef __GDK_ENUM_TYPES_H__
__GDK_ENUM_TYPES_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdkversionmacros.inc

;GType
gdk_cursor_type_get_type proto __cdecl
GDK_TYPE_CURSOR_TYPE    equ <gdk_cursor_type_get_type>

;GType
gdk_input_source_get_type proto __cdecl
GDK_TYPE_INPUT_SOURCE   equ <gdk_input_source_get_type>
;GType
gdk_input_mode_get_type proto __cdecl
GDK_TYPE_INPUT_MODE     equ <gdk_input_mode_get_type>
;GType
gdk_axis_use_get_type proto __cdecl
GDK_TYPE_AXIS_USE       equ <gdk_axis_use_get_type>
;GType
gdk_device_type_get_type proto __cdecl
GDK_TYPE_DEVICE_TYPE    equ <gdk_device_type_get_type>

;GType
gdk_drag_action_get_type proto __cdecl
GDK_TYPE_DRAG_ACTION    equ <gdk_drag_action_get_type>
;GType
gdk_drag_protocol_get_type proto __cdecl
GDK_TYPE_DRAG_PROTOCOL  equ <gdk_drag_protocol_get_type>

;GType
gdk_filter_return_get_type proto __cdecl
GDK_TYPE_FILTER_RETURN  equ <gdk_filter_return_get_type>
;GType
gdk_event_type_get_type proto __cdecl
GDK_TYPE_EVENT_TYPE     equ <gdk_event_type_get_type>
;GType
gdk_visibility_state_get_type proto __cdecl
GDK_TYPE_VISIBILITY_STATE equ <gdk_visibility_state_get_type>
;GType
gdk_touchpad_gesture_phase_get_type proto __cdecl
GDK_TYPE_TOUCHPAD_GESTURE_PHASE equ <gdk_touchpad_gesture_phase_get_type>
;GType
gdk_scroll_direction_get_type proto __cdecl
GDK_TYPE_SCROLL_DIRECTION equ <gdk_scroll_direction_get_type>
;GType
gdk_notify_type_get_type proto __cdecl
GDK_TYPE_NOTIFY_TYPE    equ <gdk_notify_type_get_type>
;GType
gdk_crossing_mode_get_type proto __cdecl
GDK_TYPE_CROSSING_MODE  equ <gdk_crossing_mode_get_type>
;GType
gdk_property_state_get_type proto __cdecl
GDK_TYPE_PROPERTY_STATE equ <gdk_property_state_get_type>
;GType
gdk_window_state_get_type proto __cdecl
GDK_TYPE_WINDOW_STATE   equ <gdk_window_state_get_type>
;GType
gdk_setting_action_get_type proto __cdecl
GDK_TYPE_SETTING_ACTION equ <gdk_setting_action_get_type>
;GType
gdk_owner_change_get_type proto __cdecl
GDK_TYPE_OWNER_CHANGE   equ <gdk_owner_change_get_type>

;GType
gdk_frame_clock_phase_get_type proto __cdecl
GDK_TYPE_FRAME_CLOCK_PHASE equ <gdk_frame_clock_phase_get_type>

;GType
gdk_prop_mode_get_type proto __cdecl
GDK_TYPE_PROP_MODE      equ <gdk_prop_mode_get_type>

;GType
gdk_byte_order_get_type proto __cdecl
GDK_TYPE_BYTE_ORDER     equ <gdk_byte_order_get_type>
;GType
gdk_modifier_type_get_type proto __cdecl
GDK_TYPE_MODIFIER_TYPE  equ <gdk_modifier_type_get_type>
;GType
gdk_modifier_intent_get_type proto __cdecl
GDK_TYPE_MODIFIER_INTENT equ <gdk_modifier_intent_get_type>
;GType
gdk_status_get_type proto __cdecl
GDK_TYPE_STATUS         equ <gdk_status_get_type>
;GType
gdk_grab_status_get_type proto __cdecl
GDK_TYPE_GRAB_STATUS    equ <gdk_grab_status_get_type>
;GType
gdk_grab_ownership_get_type proto __cdecl
GDK_TYPE_GRAB_OWNERSHIP equ <gdk_grab_ownership_get_type>
;GType
gdk_event_mask_get_type proto __cdecl
GDK_TYPE_EVENT_MASK     equ <gdk_event_mask_get_type>
;GType
gdk_gl_error_get_type proto __cdecl
GDK_TYPE_GL_ERROR       equ <gdk_gl_error_get_type>

;GType
gdk_visual_type_get_type proto __cdecl
GDK_TYPE_VISUAL_TYPE    equ <gdk_visual_type_get_type>

;GType
gdk_window_window_class_get_type proto __cdecl
GDK_TYPE_WINDOW_WINDOW_CLASS equ <gdk_window_window_class_get_type>
;GType
gdk_window_type_get_type proto __cdecl
GDK_TYPE_WINDOW_TYPE    equ <gdk_window_type_get_type>
;GType
gdk_window_attributes_type_get_type proto __cdecl
GDK_TYPE_WINDOW_ATTRIBUTES_TYPE equ <gdk_window_attributes_type_get_type>
;GType
gdk_window_hints_get_type proto __cdecl
GDK_TYPE_WINDOW_HINTS   equ <gdk_window_hints_get_type>
;GType
gdk_window_type_hint_get_type proto __cdecl
GDK_TYPE_WINDOW_TYPE_HINT equ <gdk_window_type_hint_get_type>
;GType
gdk_wm_decoration_get_type proto __cdecl
GDK_TYPE_WM_DECORATION  equ <gdk_wm_decoration_get_type>
;GType
gdk_wm_function_get_type proto __cdecl
GDK_TYPE_WM_FUNCTION    equ <gdk_wm_function_get_type>
;GType
gdk_gravity_get_type proto __cdecl
GDK_TYPE_GRAVITY        equ <gdk_gravity_get_type>
;GType
gdk_window_edge_get_type proto __cdecl
GDK_TYPE_WINDOW_EDGE    equ <gdk_window_edge_get_type>
;GType
gdk_fullscreen_mode_get_type proto __cdecl
GDK_TYPE_FULLSCREEN_MODE equ <gdk_fullscreen_mode_get_type>

endif



ifndef __GDK_TYPES_H__
__GDK_TYPES_H__ equ 1

if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib.inc
;include pango/pango.inc
include glib-object.inc
;include cairo.inc

include gdk/gdkconfig.inc

GdkAtom			typedef ptr

GDK_CURRENT_TIME	equ 0
GDK_PARENT_RELATIVE	equ 1

;ifdef __GI_SCANNER__
GdkRectangle		STRUC
x			int_t ?
y			int_t ?
width			int_t ?
height			int_t ?
GdkRectangle		ENDS
;endif

GDK_ATOM_TO_POINTER macro atom
	exitm<(atom)>
	endm

GDK_POINTER_TO_ATOM macro ptr
	exitm<((GdkAtom)(ptr))>
	endm

_GDK_MAKE_ATOM macro val
	exitm<GUINT_TO_POINTER(val)>
	endm

GDK_NONE		equ _GDK_MAKE_ATOM(0)

.enum GdkByteOrder {
    GDK_LSB_FIRST,
    GDK_MSB_FIRST
}

.enum GdkModifierType {
    GDK_SHIFT_MASK		  = 1 shl 0,
    GDK_LOCK_MASK		  = 1 shl 1,
    GDK_CONTROL_MASK		  = 1 shl 2,
    GDK_MOD1_MASK		  = 1 shl 3,
    GDK_MOD2_MASK		  = 1 shl 4,
    GDK_MOD3_MASK		  = 1 shl 5,
    GDK_MOD4_MASK		  = 1 shl 6,
    GDK_MOD5_MASK		  = 1 shl 7,
    GDK_BUTTON1_MASK		  = 1 shl 8,
    GDK_BUTTON2_MASK		  = 1 shl 9,
    GDK_BUTTON3_MASK		  = 1 shl 10,
    GDK_BUTTON4_MASK		  = 1 shl 11,
    GDK_BUTTON5_MASK		  = 1 shl 12,
    GDK_MODIFIER_RESERVED_13_MASK = 1 shl 13,
    GDK_MODIFIER_RESERVED_14_MASK = 1 shl 14,
    GDK_MODIFIER_RESERVED_15_MASK = 1 shl 15,
    GDK_MODIFIER_RESERVED_16_MASK = 1 shl 16,
    GDK_MODIFIER_RESERVED_17_MASK = 1 shl 17,
    GDK_MODIFIER_RESERVED_18_MASK = 1 shl 18,
    GDK_MODIFIER_RESERVED_19_MASK = 1 shl 19,
    GDK_MODIFIER_RESERVED_20_MASK = 1 shl 20,
    GDK_MODIFIER_RESERVED_21_MASK = 1 shl 21,
    GDK_MODIFIER_RESERVED_22_MASK = 1 shl 22,
    GDK_MODIFIER_RESERVED_23_MASK = 1 shl 23,
    GDK_MODIFIER_RESERVED_24_MASK = 1 shl 24,
    GDK_MODIFIER_RESERVED_25_MASK = 1 shl 25,
    GDK_SUPER_MASK		  = 1 shl 26,
    GDK_HYPER_MASK		  = 1 shl 27,
    GDK_META_MASK		  = 1 shl 28,
    GDK_MODIFIER_RESERVED_29_MASK = 1 shl 29,
    GDK_RELEASE_MASK		  = 1 shl 30,
    GDK_MODIFIER_MASK		  = 0x5c001fff
}

.enum GdkModifierIntent {
    GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR,
    GDK_MODIFIER_INTENT_CONTEXT_MENU,
    GDK_MODIFIER_INTENT_EXTEND_SELECTION,
    GDK_MODIFIER_INTENT_MODIFY_SELECTION,
    GDK_MODIFIER_INTENT_NO_TEXT_INPUT,
    GDK_MODIFIER_INTENT_SHIFT_GROUP,
    GDK_MODIFIER_INTENT_DEFAULT_MOD_MASK,
}

.enum GdkStatus {
    GDK_OK		= 0,
    GDK_ERROR		= -1,
    GDK_ERROR_PARAM	= -2,
    GDK_ERROR_FILE	= -3,
    GDK_ERROR_MEM	= -4
}

.enum GdkGrabStatus {
    GDK_GRAB_SUCCESS,
    GDK_GRAB_ALREADY_GRABBED,
    GDK_GRAB_INVALID_TIME,
    GDK_GRAB_NOT_VIEWABLE,
    GDK_GRAB_FROZEN,
    GDK_GRAB_FAILED
}

.enum GdkGrabOwnership {
    GDK_OWNERSHIP_NONE,
    GDK_OWNERSHIP_WINDOW,
    GDK_OWNERSHIP_APPLICATION
}

.enum GdkEventMask {
    GDK_EXPOSURE_MASK		= 1 shl 1,
    GDK_POINTER_MOTION_MASK	= 1 shl 2,
    GDK_POINTER_MOTION_HINT_MASK= 1 shl 3,
    GDK_BUTTON_MOTION_MASK	= 1 shl 4,
    GDK_BUTTON1_MOTION_MASK	= 1 shl 5,
    GDK_BUTTON2_MOTION_MASK	= 1 shl 6,
    GDK_BUTTON3_MOTION_MASK	= 1 shl 7,
    GDK_BUTTON_PRESS_MASK	= 1 shl 8,
    GDK_BUTTON_RELEASE_MASK	= 1 shl 9,
    GDK_KEY_PRESS_MASK		= 1 shl 10,
    GDK_KEY_RELEASE_MASK	= 1 shl 11,
    GDK_ENTER_NOTIFY_MASK	= 1 shl 12,
    GDK_LEAVE_NOTIFY_MASK	= 1 shl 13,
    GDK_FOCUS_CHANGE_MASK	= 1 shl 14,
    GDK_STRUCTURE_MASK		= 1 shl 15,
    GDK_PROPERTY_CHANGE_MASK	= 1 shl 16,
    GDK_VISIBILITY_NOTIFY_MASK	= 1 shl 17,
    GDK_PROXIMITY_IN_MASK	= 1 shl 18,
    GDK_PROXIMITY_OUT_MASK	= 1 shl 19,
    GDK_SUBSTRUCTURE_MASK	= 1 shl 20,
    GDK_SCROLL_MASK		= 1 shl 21,
    GDK_TOUCH_MASK		= 1 shl 22,
    GDK_SMOOTH_SCROLL_MASK	= 1 shl 23,
    GDK_TOUCHPAD_GESTURE_MASK	= 1 shl 24,
    GDK_ALL_EVENTS_MASK		= 0xFFFFFE
}

GdkPoint		STRUC
x			gint ?
y			gint ?
GdkPoint		ENDS

GDK_GL_ERROR_NOT_AVAILABLE equ 0
GDK_GL_ERROR_UNSUPPORTED_FORMAT equ 1
GDK_GL_ERROR_UNSUPPORTED_PROFILE equ 2

endif

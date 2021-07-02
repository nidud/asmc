ifndef __GDK_KEYS_H__
__GDK_KEYS_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

GdkKeymapKey		STRUC
keycode			guint ?
_group			gint ?
level			gint ?
GdkKeymapKey		ENDS


GDK_TYPE_KEYMAP equ <gdk_keymap_get_type>
GDK_KEYMAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_KEYMAP, GdkKeymap))>
	endm
GDK_IS_KEYMAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_KEYMAP))>
	endm


;GType
gdk_keymap_get_type proto __cdecl

;GdkKeymap*
gdk_keymap_get_default proto __cdecl
;GdkKeymap*
gdk_keymap_get_for_display proto __cdecl \
	       display: ptr GdkDisplay


;guint
gdk_keymap_lookup_key proto __cdecl \
		keymap: ptr GdkKeymap,
		   key: ptr GdkKeymapKey

;gboolean
gdk_keymap_translate_keyboard_state proto __cdecl \
		keymap: ptr GdkKeymap,
      hardware_keycode: guint,
		 state: GdkModifierType,
		_group: gint,
		keyval: ptr guint,
       effective_group: ptr gint,
		 level: ptr gint,
    consumed_modifiers: ptr GdkModifierType

;gboolean
gdk_keymap_get_entries_for_keyval proto __cdecl \
		keymap: ptr GdkKeymap,
		keyval: guint,
		  keys: ptr GdkKeymapKey,
		n_keys: ptr gint

;gboolean
gdk_keymap_get_entries_for_keycode proto __cdecl \
		keymap: ptr GdkKeymap,
      hardware_keycode: guint,
		  keys: ptr GdkKeymapKey,
	       keyvals: ptr guint,
	     n_entries: ptr gint


;PangoDirection
gdk_keymap_get_direction proto __cdecl \
		keymap: ptr GdkKeymap

;gboolean
gdk_keymap_have_bidi_layouts proto __cdecl \
		keymap: ptr GdkKeymap

;gboolean
gdk_keymap_get_caps_lock_state proto __cdecl \
		keymap: ptr GdkKeymap

;gboolean
gdk_keymap_get_num_lock_state proto __cdecl \
		keymap: ptr GdkKeymap

;gboolean
gdk_keymap_get_scroll_lock_state proto __cdecl \
		keymap: ptr GdkKeymap

;guint
gdk_keymap_get_modifier_state proto __cdecl \
		keymap: ptr GdkKeymap

;void
gdk_keymap_add_virtual_modifiers proto __cdecl \
		keymap: ptr GdkKeymap,
		 state: ptr GdkModifierType

;gboolean
gdk_keymap_map_virtual_modifiers proto __cdecl \
		keymap: ptr GdkKeymap,
		 state: ptr GdkModifierType

;GdkModifierType
gdk_keymap_get_modifier_mask proto __cdecl \
		keymap: ptr GdkKeymap,
		intent: GdkModifierIntent

;gchar*
gdk_keyval_name proto __cdecl \
		keyval: guint


;guint
gdk_keyval_from_name proto __cdecl \
	   keyval_name: ptr gchar

;void
gdk_keyval_convert_case proto __cdecl \
		symbol: guint,
		 lower: ptr guint,
		 upper: ptr guint

;guint
gdk_keyval_to_upper proto __cdecl \
		keyval: guint

;guint
gdk_keyval_to_lower proto __cdecl \
		keyval: guint

;gboolean
gdk_keyval_is_upper proto __cdecl \
		keyval: guint

;gboolean
gdk_keyval_is_lower proto __cdecl \
		keyval: guint

;guint32
gdk_keyval_to_unicode proto __cdecl \
		keyval: guint

;guint
gdk_unicode_to_keyval proto __cdecl \
		    wc: guint32

endif

ifndef __GDK_MAIN_H__
__GDK_MAIN_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

GDK_PRIORITY_EVENTS     equ (G_PRIORITY_DEFAULT)

gdk_parse_args proto __cdecl \
                  argc: ptr gint,
                  argv: ptr gchar

gdk_init proto __cdecl \
                  argc: ptr gint,
                  argv: ptr gchar

;gboolean
gdk_init_check proto __cdecl \
                  argc: ptr gint,
                  argv: ptr gchar

gdk_add_option_entries_libgtk_only proto __cdecl \
                _group: ptr GOptionGroup

gdk_pre_parse_libgtk_only proto __cdecl
gdk_get_program_class proto __cdecl
gdk_set_program_class proto __cdecl \
         program_class: ptr gchar


gdk_notify_startup_complete proto __cdecl
gdk_notify_startup_complete_with_id proto __cdecl \
            startup_id: ptr gchar


gdk_error_trap_push proto __cdecl
;G_GNUC_WARN_UNUSED_RESULT
gdk_error_trap_pop proto __cdecl
gdk_error_trap_pop_ignored proto __cdecl


gdk_get_display_arg_name proto __cdecl
gdk_get_display proto __cdecl

ifndef GDK_MULTIDEVICE_SAFE
;GdkGrabStatus
gdk_pointer_grab proto __cdecl \
                window: ptr GdkWindow,
          owner_events: gboolean,
            event_mask: GdkEventMask,
            confine_to: ptr GdkWindow,
                cursor: ptr GdkCursor,
                 time_: guint32

;GdkGrabStatus
gdk_keyboard_grab proto __cdecl \
                window: ptr GdkWindow,
          owner_events: gboolean,
                 time_: guint32

endif

ifndef GDK_MULTIDEVICE_SAFE
gdk_pointer_ungrab proto __cdecl \
                 time_: guint32
gdk_keyboard_ungrab proto __cdecl \
                 time_: guint32
;gboolean
gdk_pointer_is_grabbed proto __cdecl
endif

;gint
gdk_screen_width proto __cdecl
;gint
gdk_screen_height proto __cdecl

;gint
gdk_screen_width_mm proto __cdecl
;gint
gdk_screen_height_mm proto __cdecl
gdk_set_double_click_time proto __cdecl \
                  msec: guint

gdk_beep proto __cdecl
gdk_flush proto __cdecl
gdk_disable_multidevice proto __cdecl
gdk_set_allowed_backends proto __cdecl \
              backends: ptr gchar

endif

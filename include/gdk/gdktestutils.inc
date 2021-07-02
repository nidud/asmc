ifndef __GDK_TEST_UTILS_H__
__GDK_TEST_UTILS_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkwindow.inc

;void
gdk_test_render_sync proto __cdecl \
                window: ptr GdkWindow

;gboolean
gdk_test_simulate_key proto __cdecl \
                window: ptr GdkWindow,
                     x: gint,
                     y: gint,
                keyval: guint,
             modifiers: GdkModifierType,
      key_pressrelease: GdkEventType

;gboolean
gdk_test_simulate_button proto __cdecl \
                window: ptr GdkWindow,
                     x: gint,
                     y: gint,
                button: guint,
             modifiers: GdkModifierType,
   button_pressrelease: GdkEventType

endif

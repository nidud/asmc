ifndef __GDK_WIN32_DISPLAY_H__
define __GDK_WIN32_DISPLAY_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

include windows.inc

ifdef GTK_COMPILATION
GdkWin32Display         typedef _GdkWin32Display
else
GdkWin32Display         typedef GdkDisplay
endif
;GdkWin32DisplayClass    typedef _GdkWin32DisplayClass

define GDK_TYPE_WIN32_DISPLAY              <gdk_win32_display_get_type>
GDK_WIN32_DISPLAY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_DISPLAY, GdkWin32Display))>
  endm
GDK_WIN32_DISPLAY_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_DISPLAY, GdkWin32DisplayClass))>
  endm
GDK_IS_WIN32_DISPLAY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_DISPLAY))>
  endm
GDK_IS_WIN32_DISPLAY_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_DISPLAY))>
  endm
GDK_WIN32_DISPLAY_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_DISPLAY, GdkWin32DisplayClass))>
  endm

gdk_win32_display_get_type proto
gdk_win32_display_set_cursor_theme proto :ptr, :ptr, :sdword

.enum GdkWin32MessageFilterReturn {
  GDK_WIN32_MESSAGE_FILTER_CONTINUE,
  GDK_WIN32_MESSAGE_FILTER_REMOVE
}

CALLBACK(GdkWin32MessageFilterFunc, :ptr, :ptr, :ptr, :gpointer)

gdk_win32_display_add_filter proto :ptr, :GdkWin32MessageFilterFunc, :gpointer
gdk_win32_display_remove_filter proto :ptr, :GdkWin32MessageFilterFunc, :gpointer
gdk_win32_display_get_primary_monitor proto :ptr
gdk_win32_display_get_egl_display proto :ptr

endif

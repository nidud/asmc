ifndef __GDK_WIN32_SCREEN_H__
define __GDK_WIN32_SCREEN_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

define GDK_TYPE_WIN32_SCREEN <gdk_win32_screen_get_type ()>
GDK_WIN32_SCREEN macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_SCREEN, GdkWin32Screen))>
  endm
GDK_WIN32_SCREEN_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_SCREEN, GdkWin32ScreenClass))>
  endm
GDK_IS_WIN32_SCREEN macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_SCREEN))>
  endm
GDK_IS_WIN32_SCREEN_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_SCREEN))>
  endm
GDK_WIN32_SCREEN_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_SCREEN, GdkWin32ScreenClass))>
  endm

gdk_win32_screen_get_type proto

endif

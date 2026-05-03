ifndef __GDK_WIN32_DISPLAY_MANAGER_H__
define __GDK_WIN32_DISPLAY_MANAGER_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

ifdef GTK_COMPILATION
else
GdkWin32DisplayManager  typedef GdkDisplayManager
endif

define GDK_TYPE_WIN32_DISPLAY_MANAGER <gdk_win32_display_manager_get_type ()>
GDK_WIN32_DISPLAY_MANAGER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_DISPLAY_MANAGER, GdkWin32DisplayManager))>
  endm
GDK_WIN32_DISPLAY_MANAGER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_DISPLAY_MANAGER, GdkWin32DisplayManagerClass))>
  endm
GDK_IS_WIN32_DISPLAY_MANAGER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_DISPLAY_MANAGER))>
  endm
GDK_IS_WIN32_DISPLAY_MANAGER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_DISPLAY_MANAGER))>
  endm
GDK_WIN32_DISPLAY_MANAGER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_DISPLAY_MANAGER, GdkWin32DisplayManagerClass))>
  endm

gdk_win32_display_manager_get_type proto

endif

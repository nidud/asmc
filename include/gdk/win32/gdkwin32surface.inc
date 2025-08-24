ifndef __GDK_WIN32_SURFACE_H__
define __GDK_WIN32_SURFACE_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

define GDK_TYPE_WIN32_SURFACE <gdk_win32_surface_get_type ()>
GDK_WIN32_SURFACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_SURFACE, GdkWin32Surface))>
  endm
GDK_WIN32_SURFACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_SURFACE, GdkWin32SurfaceClass))>
  endm
GDK_IS_WIN32_SURFACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_SURFACE))>
  endm
GDK_IS_WIN32_SURFACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_SURFACE))>
  endm
GDK_WIN32_SURFACE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_SURFACE, GdkWin32SurfaceClass))>
  endm

gdk_win32_surface_get_type proto

gdk_win32_surface_set_urgency_hint proto :ptr, :gboolean

endif

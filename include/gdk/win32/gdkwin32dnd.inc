ifndef __GDK_WIN32_DND_H__
define __GDK_WIN32_DND_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

define GDK_TYPE_WIN32_DRAG              <gdk_win32_drag_get_type>
GDK_WIN32_DRAG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_DRAG, GdkWin32Drag))>
  endm
GDK_WIN32_DRAG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_DRAG, GdkWin32DragClass))>
  endm
GDK_IS_WIN32_DRAG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_DRAG))>
  endm
GDK_IS_WIN32_DRAG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_DRAG))>
  endm
GDK_WIN32_DRAG_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_DRAG, GdkWin32DragClass))>
  endm

ifdef GTK_COMPILATION
GdkWin32Drag            typedef _GdkWin32Drag
else
GdkWin32Drag            typedef GdkDrag
endif
;GdkWin32DragClass       typedef _GdkWin32DragClass

gdk_win32_drag_get_type proto

endif

ifndef __GDK_WIN32_CURSOR_H__
define __GDK_WIN32_CURSOR_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc
include gdk/win32/gdkwin32display.inc
include windows.inc

define GDK_TYPE_WIN32_HCURSOR <gdk_win32_hcursor_get_type ()>
GDK_WIN32_HCURSOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_HCURSOR, GdkWin32HCursor))>
  endm
GDK_WIN32_HCURSOR_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_HCURSOR, GdkWin32HCursorClass))>
  endm
GDK_IS_WIN32_HCURSOR macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_HCURSOR))>
  endm
GDK_IS_WIN32_HCURSOR_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_HCURSOR))>
  endm
GDK_WIN32_HCURSOR_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_HCURSOR, GdkWin32HCursorClass))>
  endm

gdk_win32_hcursor_get_type proto

GdkWin32HCursorFake     struct
parent_instance         GObject <>
readonly_handle         HCURSOR ?
GdkWin32HCursorFake     ends

gdk_win32_hcursor_get_handle_fast macro x
  exitm<(((struct _GdkWin32HCursorFake *) x)->readonly_handle)>
  endm

if defined (GTK_COMPILATION)
define gdk_win32_hcursor_get_handle <gdk_win32_hcursor_get_handle_fast>
else
gdk_win32_hcursor_get_handle proto :ptr
endif

gdk_win32_hcursor_new proto :ptr, :HCURSOR, :gboolean
gdk_win32_display_get_win32hcursor proto :ptr, :ptr
_gdk_win32_display_hcursor_ref proto :ptr, :HCURSOR, :gboolean
_gdk_win32_display_hcursor_unref proto :ptr, :HCURSOR

endif

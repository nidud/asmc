ifndef __GDK_WIN32_GL_CONTEXT_H__
define __GDK_WIN32_GL_CONTEXT_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

define GDK_TYPE_WIN32_GL_CONTEXT	<gdk_win32_gl_context_get_type ()>
GDK_WIN32_GL_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_WIN32_GL_CONTEXT, GdkWin32GLContext))>
  endm
GDK_WIN32_IS_GL_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_WIN32_GL_CONTEXT))>
  endm

;GdkWin32GLContext	typedef _GdkWin32GLContext
;GdkWin32GLContextClass typedef _GdkWin32GLContextClass

gdk_win32_gl_context_get_type proto
gdk_win32_display_get_wgl_version proto :ptr, :ptr, :ptr

endif

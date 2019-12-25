ifndef __GDK_GL_CONTEXT_H__
__GDK_GL_CONTEXT_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

GDK_TYPE_GL_CONTEXT equ <gdk_gl_context_get_type>
GDK_GL_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_GL_CONTEXT, GdkGLContext))>
	endm
GDK_IS_GL_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_GL_CONTEXT))>
	endm

GDK_GL_ERROR equ <gdk_gl_error_quark>

;GQuark
gdk_gl_error_quark proto __cdecl

;GType
gdk_gl_context_get_type proto __cdecl

;GdkDisplay
gdk_gl_context_get_display proto __cdecl \
	       context: ptr GdkGLContext

;GdkWindow
gdk_gl_context_get_window proto __cdecl \
	       context: ptr GdkGLContext

;GdkGLContext
gdk_gl_context_get_shared_context proto __cdecl \
	       context: ptr GdkGLContext

;void
gdk_gl_context_get_version proto __cdecl \
	       context: ptr GdkGLContext,
		 major: ptr int_t,
		 minor: ptr int_t


;void
gdk_gl_context_set_required_version proto __cdecl \
	       context: ptr GdkGLContext,
		 major: int_t,
		 minor: int_t

;void
gdk_gl_context_get_required_version proto __cdecl \
	       context: ptr GdkGLContext,
		 major: ptr int_t,
		 minor: ptr int_t

;void
gdk_gl_context_set_debug_enabled proto __cdecl \
	       context: ptr GdkGLContext,
	       enabled: gboolean

;gboolean
gdk_gl_context_get_debug_enabled proto __cdecl \
	       context: ptr GdkGLContext

;void
gdk_gl_context_set_forward_compatible proto __cdecl \
	       context: ptr GdkGLContext,
	    compatible: gboolean

;gboolean
gdk_gl_context_get_forward_compatible proto __cdecl \
	       context: ptr GdkGLContext


;gboolean
gdk_gl_context_realize proto __cdecl \
	       context: ptr GdkGLContext,
		 error: ptr GError

;void
gdk_gl_context_make_current proto __cdecl \
	       context: ptr GdkGLContext

;GdkGLContext
gdk_gl_context_get_current proto __cdecl
;void
gdk_gl_context_clear_current proto __cdecl

endif

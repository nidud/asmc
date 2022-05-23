ifndef __GDK_GL_CONTEXT_H__
define __GDK_GL_CONTEXT_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

.enum GdkGLAPI {
  GDK_GL_API_GL   = 1 shl 0,
  GDK_GL_API_GLES = 1 shl 1
}

define GDK_TYPE_GL_CONTEXT             <gdk_gl_context_get_type>
GDK_GL_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_GL_CONTEXT, GdkGLContext))>
  endm
GDK_IS_GL_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_GL_CONTEXT))>
  endm

define GDK_GL_ERROR       <gdk_gl_error_quark>

gdk_gl_error_quark proto
gdk_gl_context_get_type proto
gdk_gl_context_get_display proto :ptr
gdk_gl_context_get_surface proto :ptr
gdk_gl_context_get_shared_context proto :ptr
gdk_gl_context_get_version proto :ptr, :ptr, :ptr
gdk_gl_context_is_legacy proto :ptr
gdk_gl_context_is_shared proto :ptr, :ptr
gdk_gl_context_set_required_version proto :ptr, :sdword, :sdword
gdk_gl_context_get_required_version proto :ptr, :ptr, :ptr
gdk_gl_context_set_debug_enabled proto :ptr, :gboolean
gdk_gl_context_get_debug_enabled proto :ptr
gdk_gl_context_set_forward_compatible proto :ptr, :gboolean
gdk_gl_context_get_forward_compatible proto :ptr
gdk_gl_context_set_allowed_apis proto :ptr, :GdkGLAPI
gdk_gl_context_get_allowed_apis proto :ptr
gdk_gl_context_get_api proto :ptr
gdk_gl_context_set_use_es proto :ptr, :sdword
gdk_gl_context_get_use_es proto :ptr
gdk_gl_context_realize proto :ptr, :ptr
gdk_gl_context_make_current proto :ptr
gdk_gl_context_get_current proto
gdk_gl_context_clear_current proto

endif

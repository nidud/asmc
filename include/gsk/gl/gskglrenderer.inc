ifndef __GSK_GL_RENDERER_H__
define __GSK_GL_RENDERER_H__

include gsk/gskrenderer.inc

define GSK_TYPE_GL_RENDERER <gsk_gl_renderer_get_type ()>

GSK_GL_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_GL_RENDERER, GskGLRenderer))>
  endm
GSK_IS_GL_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_GL_RENDERER))>
  endm
GSK_GL_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GSK_TYPE_GL_RENDERER, GskGLRendererClass))>
  endm
GSK_IS_GL_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GSK_TYPE_GL_RENDERER))>
  endm
GSK_GL_RENDERER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GSK_TYPE_GL_RENDERER, GskGLRendererClass))>
  endm

GskGLRenderer           typedef _GskGLRenderer
GskGLRendererClass      typedef _GskGLRendererClass

gsk_gl_renderer_get_type proto
gsk_gl_renderer_new proto

gsk_ngl_renderer_get_type proto
gsk_ngl_renderer_new proto

endif

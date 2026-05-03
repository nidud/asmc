ifndef __GDK_GL_TEXTURE_H__
define __GDK_GL_TEXTURE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkglcontext.inc
include gdk/gdktexture.inc

define GDK_TYPE_GL_TEXTURE <gdk_gl_texture_get_type ()>

GDK_GL_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_GL_TEXTURE, GdkGLTexture))>
  endm
GDK_IS_GL_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_GL_TEXTURE))>
  endm

gdk_gl_texture_get_type proto
gdk_gl_texture_new proto :ptr, :guint, :sdword, :sdword, :GDestroyNotify, :gpointer
gdk_gl_texture_release proto :ptr

endif

ifndef __GTK_GL_AREA_H__
define __GTK_GL_AREA_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_GL_AREA <gtk_gl_area_get_type>
GTK_GL_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_GL_AREA, GtkGLArea))>
  endm
GTK_IS_GL_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_GL_AREA))>
  endm
GTK_GL_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_GL_AREA, GtkGLAreaClass))>
  endm
GTK_IS_GL_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_GL_AREA))>
  endm
GTK_GL_AREA_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_GL_AREA, GtkGLAreaClass))>
  endm

_GtkGLArea              struct
parent_instance         GtkWidget <>
_GtkGLArea              ends
GtkGLArea               typedef _GtkGLArea

_GtkGLAreaClass         struct
parent_class            GtkWidgetClass <>
render                  proc :ptr, :ptr
resize                  proc :ptr, :sdword, :sdword
create_context          proc :ptr
_padding                gpointer 8 dup(?)
_GtkGLAreaClass         ends
GtkGLAreaClass          typedef _GtkGLAreaClass

gtk_gl_area_get_type proto
gtk_gl_area_new proto
gtk_gl_area_set_use_es proto :ptr, :gboolean
gtk_gl_area_get_use_es proto :ptr
gtk_gl_area_set_required_version proto :ptr, :sdword, :sdword
gtk_gl_area_get_required_version proto :ptr, :ptr, :ptr
gtk_gl_area_get_has_depth_buffer proto :ptr
gtk_gl_area_set_has_depth_buffer proto :ptr, :gboolean
gtk_gl_area_get_has_stencil_buffer proto :ptr
gtk_gl_area_set_has_stencil_buffer proto :ptr, :gboolean
gtk_gl_area_get_auto_render proto :ptr
gtk_gl_area_set_auto_render proto :ptr, :gboolean
gtk_gl_area_queue_render proto :ptr
gtk_gl_area_get_context proto :ptr
gtk_gl_area_make_current proto :ptr
gtk_gl_area_attach_buffers proto :ptr
gtk_gl_area_set_error proto :ptr, :ptr
gtk_gl_area_get_error proto :ptr

endif

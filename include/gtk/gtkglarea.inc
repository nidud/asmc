ifndef __GTK_GL_AREA_H__
__GTK_GL_AREA_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_GL_AREA equ <gtk_gl_area_get_type>
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

GtkGLArea		STRUC
parent_instance		GtkWidget <>
GtkGLArea		ENDS

GtkGLAreaClass		STRUC
parent_class		GtkWidgetClass <>
render			proc :ptr GtkGLArea, :ptr GdkGLContext
resize			proc :ptr GtkGLArea, :int_t, :int_t
create_context		proc :ptr GtkGLArea
_padding		gpointer 6 dup(?)
GtkGLAreaClass		ENDS

;GType
gtk_gl_area_get_type proto __cdecl

;GtkWidget
gtk_gl_area_new proto __cdecl

;void
gtk_gl_area_set_required_version proto __cdecl \
		  area: ptr GtkGLArea,
		 major: gint,
		 minor: gint

;void
gtk_gl_area_get_required_version proto __cdecl \
		  area: ptr GtkGLArea,
		 major: ptr gint,
		 minor: ptr gint

;gboolean
gtk_gl_area_get_has_alpha proto __cdecl \
		  area: ptr GtkGLArea

;void
gtk_gl_area_set_has_alpha proto __cdecl \
		  area: ptr GtkGLArea,
	     has_alpha: gboolean

;gboolean
gtk_gl_area_get_has_depth_buffer proto __cdecl \
		  area: ptr GtkGLArea

;void
gtk_gl_area_set_has_depth_buffer proto __cdecl \
		  area: ptr GtkGLArea,
      has_depth_buffer: gboolean

;gboolean
gtk_gl_area_get_has_stencil_buffer proto __cdecl \
		  area: ptr GtkGLArea

;void
gtk_gl_area_set_has_stencil_buffer proto __cdecl \
		  area: ptr GtkGLArea,
    has_stencil_buffer: gboolean

;gboolean
gtk_gl_area_get_auto_render proto __cdecl \
		  area: ptr GtkGLArea

;void
gtk_gl_area_set_auto_render proto __cdecl \
		  area: ptr GtkGLArea,
	   auto_render: gboolean

;void
gtk_gl_area_queue_render proto __cdecl \
		  area: ptr GtkGLArea



;GdkGLContext
gtk_gl_area_get_context proto __cdecl \
		  area: ptr GtkGLArea


;void
gtk_gl_area_make_current proto __cdecl \
		  area: ptr GtkGLArea

;void
gtk_gl_area_attach_buffers proto __cdecl \
		  area: ptr GtkGLArea


;void
gtk_gl_area_set_error proto __cdecl \
		  area: ptr GtkGLArea,
		 error: ptr GError

;GError
gtk_gl_area_get_error proto __cdecl \
		  area: ptr GtkGLArea

G_END_DECLS

endif

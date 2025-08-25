ifndef GDK_PIXBUF_SIMPLE_ANIM_H
define GDK_PIXBUF_SIMPLE_ANIM_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include gdk-pixbuf/gdk-pixbuf-animation.inc

define GDK_TYPE_PIXBUF_SIMPLE_ANIM <gdk_pixbuf_simple_anim_get_type ()>
GDK_PIXBUF_SIMPLE_ANIM macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_PIXBUF_SIMPLE_ANIM, GdkPixbufSimpleAnim))>
	endm
GDK_IS_PIXBUF_SIMPLE_ANIM macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_PIXBUF_SIMPLE_ANIM))>
	endm

GDK_PIXBUF_SIMPLE_ANIM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_PIXBUF_SIMPLE_ANIM, GdkPixbufSimpleAnimClass))>
	endm
GDK_IS_PIXBUF_SIMPLE_ANIM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_PIXBUF_SIMPLE_ANIM))>
	endm
GDK_PIXBUF_SIMPLE_ANIM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_PIXBUF_SIMPLE_ANIM, GdkPixbufSimpleAnimClass))>
	endm

gdk_pixbuf_simple_anim_get_type proto __cdecl
gdk_pixbuf_simple_anim_iter_get_type proto __cdecl
gdk_pixbuf_simple_anim_new proto __cdecl :gint, :gint, :gfloat
gdk_pixbuf_simple_anim_add_frame proto __cdecl :ptr, :ptr
gdk_pixbuf_simple_anim_set_loop proto __cdecl :ptr, :gboolean
gdk_pixbuf_simple_anim_get_loop proto __cdecl :ptr

endif

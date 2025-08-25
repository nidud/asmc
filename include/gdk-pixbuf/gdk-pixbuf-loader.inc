ifndef GDK_PIXBUF_LOADER_H
define GDK_PIXBUF_LOADER_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib.inc
include glib-object.inc
include gdk-pixbuf/gdk-pixbuf-core.inc
include gdk-pixbuf/gdk-pixbuf-animation.inc
include gdk-pixbuf/gdk-pixbuf-io.inc

define GDK_TYPE_PIXBUF_LOADER <gdk_pixbuf_loader_get_type ()>
GDK_PIXBUF_LOADER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_PIXBUF_LOADER, GdkPixbufLoader))>
	endm
GDK_PIXBUF_LOADER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_PIXBUF_LOADER, GdkPixbufLoaderClass))>
	endm
GDK_IS_PIXBUF_LOADER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_PIXBUF_LOADER))>
	endm
GDK_IS_PIXBUF_LOADER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_PIXBUF_LOADER))>
	endm
GDK_PIXBUF_LOADER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_PIXBUF_LOADER, GdkPixbufLoaderClass))>
	endm


GdkPixbufLoader		STRUC
parent_instance		GObject <>
priv			gpointer ?
GdkPixbufLoader		ENDS

GdkPixbufLoaderClass	STRUC
parent_class		GObjectClass <>
size_prepared		proc :ptr, :SINT, :SINT
area_prepared		proc :ptr
area_updated		proc :ptr, :SINT, :SINT, :SINT, :SINT
closed			proc :ptr
GdkPixbufLoaderClass	ENDS

gdk_pixbuf_loader_get_type proto __cdecl
gdk_pixbuf_loader_new proto __cdecl
gdk_pixbuf_loader_new_with_type proto __cdecl :ptr, :ptr
gdk_pixbuf_loader_new_with_mime_type proto __cdecl :ptr, :ptr
gdk_pixbuf_loader_set_size proto __cdecl :ptr, :SINT, :SINT
gdk_pixbuf_loader_write proto __cdecl :ptr, :ptr, :gsize, :ptr
gdk_pixbuf_loader_write_bytes proto __cdecl :ptr, :ptr, :ptr
gdk_pixbuf_loader_get_pixbuf proto __cdecl :ptr
gdk_pixbuf_loader_get_animation proto __cdecl :ptr
gdk_pixbuf_loader_close proto __cdecl :ptr, :ptr
gdk_pixbuf_loader_get_format proto __cdecl :ptr

endif

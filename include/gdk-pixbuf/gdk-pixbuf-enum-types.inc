ifndef __GDK_PIXBUF_ENUM_TYPES_H__
define __GDK_PIXBUF_ENUM_TYPES_H__

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib-object.inc
include gdk-pixbuf/gdk-pixbuf-macros.inc

gdk_pixbuf_alpha_mode_get_type proto __cdecl
define GDK_TYPE_PIXBUF_ALPHA_MODE <gdk_pixbuf_alpha_mode_get_type ()>
gdk_colorspace_get_type proto __cdecl
define GDK_TYPE_COLORSPACE     <gdk_colorspace_get_type ()>
gdk_pixbuf_error_get_type proto __cdecl
define GDK_TYPE_PIXBUF_ERROR   <gdk_pixbuf_error_get_type ()>
gdk_interp_type_get_type proto __cdecl
define GDK_TYPE_INTERP_TYPE    <gdk_interp_type_get_type ()>
gdk_pixbuf_rotation_get_type proto __cdecl
define GDK_TYPE_PIXBUF_ROTATION <gdk_pixbuf_rotation_get_type ()>

endif

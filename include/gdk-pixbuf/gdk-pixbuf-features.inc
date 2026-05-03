ifndef __GDK_PIXBUF_FEATURES_H__
define __GDK_PIXBUF_FEATURES_H__

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib.inc

define GDK_PIXBUF_MAJOR   2
define GDK_PIXBUF_MINOR   42
define GDK_PIXBUF_MICRO   8
define GDK_PIXBUF_VERSION <"2.42.8">

externdef gdk_pixbuf_major_version:guint
externdef gdk_pixbuf_minor_version:guint
externdef gdk_pixbuf_micro_version:guint
externdef gdk_pixbuf_version:string_t

endif

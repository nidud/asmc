ifndef __GDK_PIXBUF_H__
define __GDK_PIXBUF_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include cairo.inc
include gdk-pixbuf/gdk-pixbuf.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc
include gdk/gdktexture.inc

gdk_pixbuf_get_from_surface proto :ptr, :sdword, :sdword, :sdword, :sdword
gdk_pixbuf_get_from_texture proto :ptr

endif

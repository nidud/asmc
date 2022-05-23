ifndef __GDK_RGBA_H__
define __GDK_RGBA_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

_GdkRGBA                struct
red                     real4 ?
green                   real4 ?
blue                    real4 ?
alpha                   real4 ?
_GdkRGBA                ends
GdkRGBA                 typedef _GdkRGBA

define GDK_TYPE_RGBA <gdk_rgba_get_type>

gdk_rgba_get_type proto
gdk_rgba_copy proto :ptr
gdk_rgba_free proto :ptr
gdk_rgba_is_clear proto :ptr
gdk_rgba_is_opaque proto :ptr
gdk_rgba_hash proto :gconstpointer
gdk_rgba_equal proto :gconstpointer, :gconstpointer
gdk_rgba_parse proto :ptr, :ptr
gdk_rgba_to_string proto :ptr

endif

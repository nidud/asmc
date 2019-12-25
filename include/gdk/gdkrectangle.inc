ifndef __GDK_RECTANGLE_H__
__GDK_RECTANGLE_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;gboolean
gdk_rectangle_intersect proto __cdecl \
                  src1: ptr GdkRectangle,
                  src2: ptr GdkRectangle,
                  dest: ptr GdkRectangle

;void
gdk_rectangle_union proto __cdecl \
                  src1: ptr GdkRectangle,
                  src2: ptr GdkRectangle,
                  dest: ptr GdkRectangle


;GType
gdk_rectangle_get_type proto __cdecl

GDK_TYPE_RECTANGLE      equ <gdk_rectangle_get_type>

endif

ifndef __GDK_RECTANGLE_H__
define __GDK_RECTANGLE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

gdk_rectangle_intersect proto :ptr, :ptr, :ptr
gdk_rectangle_union proto :ptr, :ptr, :ptr
gdk_rectangle_equal proto :ptr, :ptr
gdk_rectangle_contains_point proto :ptr, :sdword, :sdword
gdk_rectangle_get_type proto

define GDK_TYPE_RECTANGLE <gdk_rectangle_get_type ()>

endif

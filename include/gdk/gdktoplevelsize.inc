ifndef __GDK_TOPLEVEL_SIZE_H__
define __GDK_TOPLEVEL_SIZE_H__

if not defined(__GDK_H_INSIDE__) and not defined(GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;GdkToplevelSize         typedef _GdkToplevelSize

define GDK_TYPE_TOPLEVEL_SIZE <gdk_toplevel_size_get_type ()>

gdk_toplevel_size_get_type proto
gdk_toplevel_size_get_bounds proto :ptr, :ptr, :ptr
gdk_toplevel_size_set_size proto :ptr, :sdword, :sdword
gdk_toplevel_size_set_min_size proto :ptr, :sdword, :sdword
gdk_toplevel_size_set_shadow_width proto :ptr, :sdword, :sdword, :sdword, :sdword

endif

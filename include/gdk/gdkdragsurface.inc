ifndef __GDK_DRAG_SURFACE_H__
define __GDK_DRAG_SURFACE_H__

if not defined(__GDK_H_INSIDE__) and not defined(GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdksurface.inc

define GDK_TYPE_DRAG_SURFACE <gdk_drag_surface_get_type>

gdk_drag_surface_present proto :ptr, :sdword, :sdword

endif

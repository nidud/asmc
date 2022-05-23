ifndef __GDK_POPUP_H__
define __GDK_POPUP_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkpopuplayout.inc
include gdk/gdksurface.inc

define GDK_TYPE_POPUP <gdk_popup_get_type>

gdk_popup_present proto :ptr, :sdword, :sdword, :ptr
gdk_popup_get_surface_anchor proto :ptr
gdk_popup_get_rect_anchor proto :ptr
gdk_popup_get_parent proto :ptr
gdk_popup_get_position_x proto :ptr
gdk_popup_get_position_y proto :ptr
gdk_popup_get_autohide proto :ptr

endif

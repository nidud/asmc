ifndef __GTK_DRAG_ICON_H__
define __GTK_DRAG_ICON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_DRAG_ICON <gtk_drag_icon_get_type>

gtk_drag_icon_get_for_drag proto :ptr
gtk_drag_icon_set_child proto :ptr, :ptr
gtk_drag_icon_get_child proto :ptr
gtk_drag_icon_set_from_paintable proto :ptr, :ptr, :sdword, :sdword
gtk_drag_icon_create_widget_for_value proto :ptr

endif

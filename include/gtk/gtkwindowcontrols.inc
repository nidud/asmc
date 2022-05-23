ifndef __GTK_WINDOW_CONTROLS_H__
define __GTK_WINDOW_CONTROLS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_WINDOW_CONTROLS <gtk_window_controls_get_type>

gtk_window_controls_new proto :GtkPackType
gtk_window_controls_get_side proto :ptr
gtk_window_controls_set_side proto :ptr, :GtkPackType
gtk_window_controls_get_decoration_layout proto :ptr
gtk_window_controls_set_decoration_layout proto :ptr, :ptr
gtk_window_controls_get_empty proto :ptr

endif


ifndef __GTK_ROOT_H__
define __GTK_ROOT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkwidget.inc

define GTK_TYPE_ROOT <gtk_root_get_type ()>

gtk_root_get_display proto :ptr
gtk_root_set_focus proto :ptr, :ptr
gtk_root_get_focus proto :ptr

endif

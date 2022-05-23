ifndef __GTK_NATIVE_H__
define __GTK_NATIVE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkwidget.inc

define GTK_TYPE_NATIVE <gtk_native_get_type>

gtk_native_realize proto :ptr
gtk_native_unrealize proto :ptr
gtk_native_get_for_surface proto :ptr
gtk_native_get_surface proto :ptr
gtk_native_get_renderer proto :ptr
gtk_native_get_surface_transform proto :ptr, :ptr, :ptr

endif

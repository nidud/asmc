ifndef __GTK_COLOR_UTILS_H__
define __GTK_COLOR_UTILS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gdk/gdk.inc

gtk_hsv_to_rgb proto :real4, :real4, :real4, :ptr, :ptr, :ptr
gtk_rgb_to_hsv proto :real4, :real4, :real4, :ptr, :ptr, :ptr

endif

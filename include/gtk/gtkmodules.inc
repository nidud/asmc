ifndef __GTK_MODULES_H__
define __GTK_MODULES_H__
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

CALLBACKC(GtkModuleInitFunc, :ptr gint, :ptr ptr gchar)
CALLBACKC(GtkModuleDisplayInitFunc, :ptr GdkDisplay)

endif

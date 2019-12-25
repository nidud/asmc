ifndef __GTK_MODULES_H__
__GTK_MODULES_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

G_BEGIN_DECLS

CALLBACKC(GtkModuleInitFunc, :ptr gint, :ptr ptr gchar)
CALLBACKC(GtkModuleDisplayInitFunc, :ptr GdkDisplay)

G_END_DECLS

endif

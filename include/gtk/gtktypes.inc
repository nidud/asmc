ifndef __GTK_TYPES_H__
__GTK_TYPES_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

CALLBACKC(GtkRcPropertyParser, :ptr GParamSpec, :ptr GString, :ptr GValue)
CALLBACKC(GtkBuilderConnectFunc, :ptr GtkBuilder, :ptr GObject, :ptr gchar, :ptr gchar, :ptr GObject, :GConnectFlags, :gpointer)

endif

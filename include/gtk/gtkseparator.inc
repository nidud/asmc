ifndef __GTK_SEPARATOR_H__
define __GTK_SEPARATOR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SEPARATOR <gtk_separator_get_type ()>
GTK_SEPARATOR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEPARATOR, GtkSeparator))>
  endm
GTK_IS_SEPARATOR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEPARATOR))>
  endm

gtk_separator_get_type proto
gtk_separator_new proto :GtkOrientation

endif

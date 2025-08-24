ifndef __GTK_SCROLLBAR_H__
define __GTK_SCROLLBAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SCROLLBAR <gtk_scrollbar_get_type ()>
GTK_SCROLLBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCROLLBAR, GtkScrollbar))>
  endm
GTK_IS_SCROLLBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCROLLBAR))>
  endm

gtk_scrollbar_get_type proto
gtk_scrollbar_new proto :GtkOrientation, :ptr
gtk_scrollbar_set_adjustment proto :ptr, :ptr
gtk_scrollbar_get_adjustment proto :ptr

endif

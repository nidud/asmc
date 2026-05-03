ifndef __GTK_LIST_BASE_H__
define __GTK_LIST_BASE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkselectionmodel.inc

define GTK_TYPE_LIST_BASE <gtk_list_base_get_type ()>
GTK_LIST_BASE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LIST_BASE, GtkListBase))>
  endm
GTK_LIST_BASE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_LIST_BASE, GtkListBaseClass))>
  endm
GTK_IS_LIST_BASE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LIST_BASE))>
  endm
GTK_IS_LIST_BASE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LIST_BASE))>
  endm
GTK_LIST_BASE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LIST_BASE, GtkListBaseClass))>
  endm

gtk_list_base_get_type proto

endif

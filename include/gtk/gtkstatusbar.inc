ifndef __GTK_STATUSBAR_H__
define __GTK_STATUSBAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_STATUSBAR <gtk_statusbar_get_type>
GTK_STATUSBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STATUSBAR, GtkStatusbar))>
  endm
GTK_IS_STATUSBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STATUSBAR))>
  endm

;GtkStatusbar            typedef _GtkStatusbar

gtk_statusbar_get_type proto
gtk_statusbar_new proto
gtk_statusbar_get_context_id proto :ptr, :ptr
gtk_statusbar_push proto :ptr, :guint, :ptr
gtk_statusbar_pop proto :ptr, :guint
gtk_statusbar_remove proto :ptr, :guint, :guint
gtk_statusbar_remove_all proto :ptr, :guint

endif

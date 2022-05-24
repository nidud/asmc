ifndef __GTK_VIEWPORT_H__
define __GTK_VIEWPORT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_VIEWPORT <gtk_viewport_get_type ()>
GTK_VIEWPORT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VIEWPORT, GtkViewport))>
  endm
GTK_IS_VIEWPORT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VIEWPORT))>
  endm

;GtkViewport             typedef _GtkViewport

gtk_viewport_get_type proto
gtk_viewport_new proto :ptr, :ptr
gtk_viewport_get_scroll_to_focus proto :ptr
gtk_viewport_set_scroll_to_focus proto :ptr, :gboolean
gtk_viewport_set_child proto :ptr, :ptr
gtk_viewport_get_child proto :ptr

endif

ifndef __GTK_SPINNER_H__
define __GTK_SPINNER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SPINNER <gtk_spinner_get_type ()>
GTK_SPINNER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SPINNER, GtkSpinner))>
  endm
GTK_IS_SPINNER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SPINNER))>
  endm

;GtkSpinner              typedef _GtkSpinner

gtk_spinner_get_type proto
gtk_spinner_new proto
gtk_spinner_start proto :ptr
gtk_spinner_stop proto :ptr
gtk_spinner_set_spinning proto :ptr, :gboolean
gtk_spinner_get_spinning proto :ptr

endif

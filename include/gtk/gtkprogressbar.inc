ifndef __GTK_PROGRESS_BAR_H__
define __GTK_PROGRESS_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_PROGRESS_BAR <gtk_progress_bar_get_type>
GTK_PROGRESS_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PROGRESS_BAR, GtkProgressBar))>
  endm
GTK_IS_PROGRESS_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PROGRESS_BAR))>
  endm

;GtkProgressBar          typedef _GtkProgressBar

gtk_progress_bar_get_type proto
gtk_progress_bar_new proto

gtk_progress_bar_pulse proto :ptr
gtk_progress_bar_set_text proto :ptr, :ptr
gtk_progress_bar_set_fraction proto :ptr, :real8

gtk_progress_bar_set_pulse_step proto :ptr, :real8
gtk_progress_bar_set_inverted proto :ptr, :gboolean

gtk_progress_bar_get_text proto :ptr
gtk_progress_bar_get_fraction proto :ptr
gtk_progress_bar_get_pulse_step proto :ptr

gtk_progress_bar_get_inverted proto :ptr
gtk_progress_bar_set_ellipsize proto :ptr, :PangoEllipsizeMode
gtk_progress_bar_get_ellipsize proto :ptr

gtk_progress_bar_set_show_text proto :ptr, :gboolean
gtk_progress_bar_get_show_text proto :ptr

endif

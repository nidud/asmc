ifndef __GTK_COLOR_CHOOSER_WIDGET_H__
define __GTK_COLOR_CHOOSER_WIDGET_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_COLOR_CHOOSER_WIDGET <gtk_color_chooser_widget_get_type ()>
GTK_COLOR_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COLOR_CHOOSER_WIDGET, GtkColorChooserWidget))>
  endm
GTK_IS_COLOR_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COLOR_CHOOSER_WIDGET))>
  endm

gtk_color_chooser_widget_get_type proto
gtk_color_chooser_widget_new proto

endif

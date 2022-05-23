ifndef __GTK_APP_CHOOSER_WIDGET_H__
define __GTK_APP_CHOOSER_WIDGET_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gio/gio.inc

define GTK_TYPE_APP_CHOOSER_WIDGET <gtk_app_chooser_widget_get_type>
GTK_APP_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_WIDGET, GtkAppChooserWidget))>
  endm
GTK_IS_APP_CHOOSER_WIDGET macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_WIDGET))>
  endm

;GtkAppChooserWidget     typedef _GtkAppChooserWidget

gtk_app_chooser_widget_get_type proto
gtk_app_chooser_widget_new proto :ptr
gtk_app_chooser_widget_set_show_default proto :ptr, :gboolean
gtk_app_chooser_widget_get_show_default proto :ptr
gtk_app_chooser_widget_set_show_recommended proto :ptr, :gboolean
gtk_app_chooser_widget_get_show_recommended proto :ptr
gtk_app_chooser_widget_set_show_fallback proto :ptr, :gboolean
gtk_app_chooser_widget_get_show_fallback proto :ptr
gtk_app_chooser_widget_set_show_other proto :ptr, :gboolean
gtk_app_chooser_widget_get_show_other proto :ptr
gtk_app_chooser_widget_set_show_all proto :ptr, :gboolean
gtk_app_chooser_widget_get_show_all proto :ptr
gtk_app_chooser_widget_set_default_text proto :ptr, :ptr
gtk_app_chooser_widget_get_default_text proto :ptr

endif

ifndef __GTK_APP_CHOOSER_H__
define __GTK_APP_CHOOSER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gio/gio.inc
include gdk/gdk.inc

define GTK_TYPE_APP_CHOOSER    <gtk_app_chooser_get_type>
GTK_APP_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER, GtkAppChooser))>
  endm
GTK_IS_APP_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER))>
  endm

;GtkAppChooser           typedef _GtkAppChooser

gtk_app_chooser_get_type proto

gtk_app_chooser_get_app_info proto :ptr
gtk_app_chooser_get_content_type proto :ptr
gtk_app_chooser_refresh proto :ptr

endif


ifndef __GTK_APPLICATION_WINDOW_H__
define __GTK_APPLICATION_WINDOW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc
include gtk/gtkshortcutswindow.inc

define GTK_TYPE_APPLICATION_WINDOW <gtk_application_window_get_type ()>
GTK_APPLICATION_WINDOW macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindow))>
  endm
GTK_APPLICATION_WINDOW_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindowClass))>
  endm
GTK_IS_APPLICATION_WINDOW macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), GTK_TYPE_APPLICATION_WINDOW))>
  endm
GTK_IS_APPLICATION_WINDOW_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), GTK_TYPE_APPLICATION_WINDOW))>
  endm
GTK_APPLICATION_WINDOW_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindowClass))>
  endm

GtkApplicationWindow    struct
parent_instance         GtkWindow <>
GtkApplicationWindow    ends

GtkApplicationWindowClass struct
parent_class            GtkWindowClass <>
padding                 gpointer 8 dup(?)
GtkApplicationWindowClass ends

gtk_application_window_get_type proto
gtk_application_window_new proto :ptr
gtk_application_window_set_show_menubar proto :ptr, :gboolean
gtk_application_window_get_show_menubar proto :ptr
gtk_application_window_get_id proto :ptr
gtk_application_window_set_help_overlay proto :ptr, :ptr
gtk_application_window_get_help_overlay proto :ptr

endif

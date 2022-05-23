ifndef __GTK_APPLICATION_H__
define __GTK_APPLICATION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gio/gio.inc

define GTK_TYPE_APPLICATION            <gtk_application_get_type>
GTK_APPLICATION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APPLICATION, GtkApplication))>
  endm
GTK_APPLICATION_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_APPLICATION, GtkApplicationClass))>
  endm
GTK_IS_APPLICATION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APPLICATION))>
  endm
GTK_IS_APPLICATION_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_APPLICATION))>
  endm
GTK_APPLICATION_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_APPLICATION, GtkApplicationClass))>
  endm

_GtkApplication         struct
parent_instance         GApplication <>
_GtkApplication         ends
GtkApplication          typedef _GtkApplication

_GtkApplicationClass    struct
parent_class            GApplicationClass <>
window_added            proc :ptr, :ptr
window_removed          proc :ptr, :ptr
padding                 gpointer 8 dup(?)
_GtkApplicationClass    ends
GtkApplicationClass     typedef _GtkApplicationClass

gtk_application_get_type proto

gtk_application_new proto :ptr, :GApplicationFlags

gtk_application_add_window proto :ptr, :ptr

gtk_application_remove_window proto :ptr, :ptr
gtk_application_get_windows proto :ptr

gtk_application_get_menubar proto :ptr
gtk_application_set_menubar proto :ptr, :ptr

.enum GtkApplicationInhibitFlags {
  GTK_APPLICATION_INHIBIT_LOGOUT  = (1 shl 0),
  GTK_APPLICATION_INHIBIT_SWITCH  = (1 shl 1),
  GTK_APPLICATION_INHIBIT_SUSPEND = (1 shl 2),
  GTK_APPLICATION_INHIBIT_IDLE    = (1 shl 3)
}

gtk_application_inhibit proto :ptr, :ptr, :GtkApplicationInhibitFlags, :ptr
gtk_application_uninhibit proto :ptr, :guint

gtk_application_get_window_by_id proto :ptr, :guint

gtk_application_get_active_window proto :ptr

gtk_application_list_action_descriptions proto :ptr

gtk_application_get_accels_for_action proto :ptr, :ptr
gtk_application_get_actions_for_accel proto :ptr, :ptr

gtk_application_set_accels_for_action proto :ptr, :ptr, :ptr

gtk_application_get_menu_by_id proto :ptr, :ptr

endif

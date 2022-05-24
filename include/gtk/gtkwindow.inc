ifndef __GTK_WINDOW_H__
define __GTK_WINDOW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkapplication.inc
include gtk/gtkaccelgroup.inc
include gtk/gtkwidget.inc

define GTK_TYPE_WINDOW <gtk_window_get_type ()>
GTK_WINDOW macro obj
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_WINDOW, GtkWindow)>
  endm
GTK_WINDOW_CLASS macro klass
  exitm<G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW, GtkWindowClass)>
  endm
GTK_IS_WINDOW macro obj
  exitm<G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_WINDOW)>
  endm
GTK_IS_WINDOW_CLASS macro klass
  exitm<G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW)>
  endm
GTK_WINDOW_GET_CLASS macro obj
  exitm<G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW, GtkWindowClass)>
  endm

;GtkWindowGroup		 typedef _GtkWindowGroup
;GtkWindowGroupClass	 typedef _GtkWindowGroupClass
;GtkWindowGroupPrivate	 typedef _GtkWindowGroupPrivate

_GtkWindow		struct
parent_instance		GtkWidget <>
_GtkWindow		ends
GtkWindow		typedef _GtkWindow


_GtkWindowClass		struct
parent_class		GtkWidgetClass <>
activate_focus		proc :ptr
activate_default	proc :ptr
keys_changed		proc :ptr
enable_debugging	proc :ptr, :gboolean
close_request		proc :ptr
padding			gpointer 8 dup(?)
_GtkWindowClass		ends
GtkWindowClass		typedef _GtkWindowClass

gtk_window_get_type proto
gtk_window_new proto
gtk_window_set_title proto :ptr, :ptr
gtk_window_get_title proto :ptr
gtk_window_set_startup_id proto :ptr, :ptr
gtk_window_set_focus proto :ptr, :ptr
gtk_window_get_focus proto :ptr
gtk_window_set_default_widget proto :ptr, :ptr
gtk_window_get_default_widget proto :ptr

gtk_window_set_transient_for proto :ptr, :ptr
gtk_window_get_transient_for proto :ptr
gtk_window_set_destroy_with_parent proto :ptr, :gboolean
gtk_window_get_destroy_with_parent proto :ptr
gtk_window_set_hide_on_close proto :ptr, :gboolean
gtk_window_get_hide_on_close proto :ptr
gtk_window_set_mnemonics_visible proto :ptr, :gboolean
gtk_window_get_mnemonics_visible proto :ptr
gtk_window_set_focus_visible proto :ptr, :gboolean
gtk_window_get_focus_visible proto :ptr

gtk_window_set_resizable proto :ptr, :gboolean
gtk_window_get_resizable proto :ptr

gtk_window_set_display proto :ptr, :ptr

gtk_window_is_active proto :ptr

gtk_window_set_decorated proto :ptr, :gboolean
gtk_window_get_decorated proto :ptr
gtk_window_set_deletable proto :ptr, :gboolean
gtk_window_get_deletable proto :ptr

gtk_window_set_icon_name proto :ptr, :ptr
gtk_window_get_icon_name proto :ptr
gtk_window_set_default_icon_name proto :ptr
gtk_window_get_default_icon_name proto

gtk_window_set_auto_startup_notification proto :gboolean


gtk_window_set_modal proto :ptr, :gboolean
gtk_window_get_modal proto :ptr
gtk_window_get_toplevels proto
gtk_window_list_toplevels proto

gtk_window_present proto :ptr
gtk_window_present_with_time proto :ptr, :guint32
gtk_window_minimize proto :ptr
gtk_window_unminimize proto :ptr
gtk_window_maximize proto :ptr
gtk_window_unmaximize proto :ptr
gtk_window_fullscreen proto :ptr
gtk_window_unfullscreen proto :ptr
gtk_window_fullscreen_on_monitor proto :ptr, :ptr
gtk_window_close proto :ptr


gtk_window_set_default_size proto :ptr, :sdword, :sdword
gtk_window_get_default_size proto :ptr, :ptr, :ptr

gtk_window_get_group proto :ptr
gtk_window_has_group proto :ptr


gtk_window_get_application proto :ptr
gtk_window_set_application proto :ptr, :ptr

gtk_window_set_child proto :ptr, :ptr
gtk_window_get_child proto :ptr

gtk_window_set_titlebar proto :ptr, :ptr
gtk_window_get_titlebar proto :ptr

gtk_window_is_maximized proto :ptr

gtk_window_is_fullscreen proto :ptr

gtk_window_destroy proto :ptr

gtk_window_set_interactive_debugging proto :gboolean

gtk_window_set_handle_menubar_accel proto :ptr, :gboolean
gtk_window_get_handle_menubar_accel proto :ptr

endif

ifndef __GTK_APPLICATION_H__
__GTK_APPLICATION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gio/gio.inc

GTK_TYPE_APPLICATION  equ <gtk_application_get_type>
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

GtkApplication		STRUC
parent			GApplication <>
priv			ptr_t ?
GtkApplication		ENDS

GtkApplicationClass	STRUC
parent_class		GApplicationClass <>
window_added		proc :ptr GtkApplication, :ptr GtkWindow
window_removed		proc :ptr GtkApplication, :ptr GtkWindow
padding			gpointer 12 dup(?)
GtkApplicationClass	ENDS

;GType
gtk_application_get_type proto __cdecl

;GtkApplication
gtk_application_new proto __cdecl \
	application_id: ptr gchar,
		 flags: GApplicationFlags


;void
gtk_application_add_window proto __cdecl \
	   application: ptr GtkApplication,
		window: ptr GtkWindow


;void
gtk_application_remove_window proto __cdecl \
	   application: ptr GtkApplication,
		window: ptr GtkWindow

;GList
gtk_application_get_windows proto __cdecl \
	   application: ptr GtkApplication


;GMenuModel
gtk_application_get_app_menu proto __cdecl \
	   application: ptr GtkApplication

;void
gtk_application_set_app_menu proto __cdecl \
	   application: ptr GtkApplication,
	      app_menu: ptr GMenuModel


;GMenuModel
gtk_application_get_menubar proto __cdecl \
	   application: ptr GtkApplication

;void
gtk_application_set_menubar proto __cdecl \
	   application: ptr GtkApplication,
	       menubar: ptr GMenuModel


;void
gtk_application_add_accelerator proto __cdecl \
	   application: ptr GtkApplication,
	   accelerator: ptr gchar,
	   action_name: ptr gchar,
	     parameter: ptr GVariant


;void
gtk_application_remove_accelerator proto __cdecl \
	   application: ptr GtkApplication,
	   action_name: ptr gchar,
	     parameter: ptr GVariant


.enum GtkApplicationInhibitFlags {
  GTK_APPLICATION_INHIBIT_LOGOUT  = (1 shl 0),
  GTK_APPLICATION_INHIBIT_SWITCH  = (1 shl 1),
  GTK_APPLICATION_INHIBIT_SUSPEND = (1 shl 2),
  GTK_APPLICATION_INHIBIT_IDLE	  = (1 shl 3)
}

;guint
gtk_application_inhibit proto __cdecl \
	   application: ptr GtkApplication,
		window: ptr GtkWindow,
		 flags: GtkApplicationInhibitFlags,
		reason: ptr gchar

;void
gtk_application_uninhibit proto __cdecl \
	   application: ptr GtkApplication,
		cookie: guint

;gboolean
gtk_application_is_inhibited proto __cdecl \
	   application: ptr GtkApplication,
		 flags: GtkApplicationInhibitFlags


;GtkWindow
gtk_application_get_window_by_id proto __cdecl \
	   application: ptr GtkApplication,
		    id: guint


;GtkWindow
gtk_application_get_active_window proto __cdecl \
	   application: ptr GtkApplication


;gchar
gtk_application_list_action_descriptions proto __cdecl \
	   application: ptr GtkApplication


;gchar
gtk_application_get_accels_for_action proto __cdecl \
	   application: ptr GtkApplication,
  detailed_action_name: ptr gchar

;gchar
gtk_application_get_actions_for_accel proto __cdecl \
	   application: ptr GtkApplication,
		 accel: ptr gchar



;void
gtk_application_set_accels_for_action proto __cdecl \
	   application: ptr GtkApplication,
  detailed_action_name: ptr gchar,
		accels: ptr ptr gchar


;gboolean
gtk_application_prefers_app_menu proto __cdecl \
	   application: ptr GtkApplication


;GMenu
gtk_application_get_menu_by_id proto __cdecl \
	   application: ptr GtkApplication,
		    id: ptr gchar


endif

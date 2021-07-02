ifndef __G_APPLICATION_H__
__G_APPLICATION_H__ equ <>
if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

G_BEGIN_DECLS

G_TYPE_APPLICATION equ <g_application_get_type>
G_APPLICATION macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_APPLICATION, GApplication))>
	endm
G_APPLICATION_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_APPLICATION, GApplicationClass))>
	endm
G_IS_APPLICATION macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_APPLICATION))>
	endm
G_IS_APPLICATION_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_APPLICATION))>
	endm
G_APPLICATION_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_APPLICATION, GApplicationClass))>
	endm


GApplication		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GApplication		ENDS

GApplicationClass	STRUC
parent_class		GObjectClass <>
startup			proc :ptr GApplication
activate		proc :ptr GApplication
open			proc :ptr GApplication, :ptr GFile, :gint, :ptr gchar
command_line		proc :ptr GApplication, :ptr GApplicationCommandLine
local_command_line	proc :ptr GApplication, :ptr gchar, :ptr int_t
before_emit		proc :ptr GApplication, :ptr GVariant
after_emit		proc :ptr GApplication, :ptr GVariant
add_platform_data	proc :ptr GApplication, :ptr GVariantBuilder
quit_mainloop		proc :ptr GApplication
run_mainloop		proc :ptr GApplication
shutdown		proc :ptr GApplication
dbus_register		proc :ptr GApplication, :ptr GDBusConnection, :ptr gchar, :ptr GError
dbus_unregister		proc :ptr GApplication, :ptr GDBusConnection, :ptr gchar
handle_local_options	proc :ptr GApplication, :ptr GVariantDict
padding			gpointer 8 dup(?)
GApplicationClass	ENDS

;GType
g_application_get_type proto __cdecl

;gboolean
g_application_id_is_valid proto __cdecl \
	application_id: ptr gchar


;GApplication
g_application_new proto __cdecl \
	application_id: ptr gchar,
		 flags: GApplicationFlags


;const
g_application_get_application_id proto __cdecl \
	   application: ptr GApplication

;void
g_application_set_application_id proto __cdecl \
	   application: ptr GApplication,
	application_id: ptr gchar


;GDBusConnection
g_application_get_dbus_connection proto __cdecl \
	   application: ptr GApplication

;const
g_application_get_dbus_object_path proto __cdecl \
	   application: ptr GApplication


;guint
g_application_get_inactivity_timeout proto __cdecl \
	   application: ptr GApplication

;void
g_application_set_inactivity_timeout proto __cdecl \
	   application: ptr GApplication,
    inactivity_timeout: guint


;GApplicationFlags
g_application_get_flags proto __cdecl \
	   application: ptr GApplication

;void
g_application_set_flags proto __cdecl \
	   application: ptr GApplication,
		 flags: GApplicationFlags


;const
g_application_get_resource_base_path proto __cdecl \
	   application: ptr GApplication

;void
g_application_set_resource_base_path proto __cdecl \
	   application: ptr GApplication,
	 resource_path: ptr gchar



;void
g_application_set_action_group proto __cdecl \
	   application: ptr GApplication,
	  action_group: ptr GActionGroup


;void
g_application_add_main_option_entries proto __cdecl \
	   application: ptr GApplication,
	       entries: ptr GOptionEntry


;void
g_application_add_main_option proto __cdecl \
	   application: ptr GApplication,
	     long_name: ptr char_t,
	    short_name: char_t,
		 flags: GOptionFlags,
		   arg: GOptionArg,
	   description: ptr char_t,
       arg_description: ptr char_t

;void
g_application_add_option_group proto __cdecl \
	   application: ptr GApplication,
		_group: ptr GOptionGroup


;gboolean
g_application_get_is_registered proto __cdecl \
	   application: ptr GApplication

;gboolean
g_application_get_is_remote proto __cdecl \
	   application: ptr GApplication


;gboolean
g_application_register proto __cdecl \
	   application: ptr GApplication,
	   cancellable: ptr GCancellable,
		 error: ptr GError


;void
g_application_hold proto __cdecl \
	   application: ptr GApplication

;void
g_application_release proto __cdecl \
	   application: ptr GApplication


;void
g_application_activate proto __cdecl \
	   application: ptr GApplication


;void
g_application_open proto __cdecl \
	   application: ptr GApplication,
		 files: ptr GFile,
	       n_files: gint,
		  hint: ptr gchar


;int
g_application_run proto __cdecl \
	   application: ptr GApplication,
		  argc: int_t,
		  argv: ptr char_t


;void
g_application_quit proto __cdecl \
	   application: ptr GApplication


;GApplication
g_application_get_default proto __cdecl
;void
g_application_set_default proto __cdecl \
	   application: ptr GApplication


;void
g_application_mark_busy proto __cdecl \
	   application: ptr GApplication

;void
g_application_unmark_busy proto __cdecl \
	   application: ptr GApplication

;gboolean
g_application_get_is_busy proto __cdecl \
	   application: ptr GApplication


;void
g_application_send_notification proto __cdecl \
	   application: ptr GApplication,
		    id: ptr gchar,
	  notification: ptr GNotification

;void
g_application_withdraw_notification proto __cdecl \
	   application: ptr GApplication,
		    id: ptr gchar


;void
g_application_bind_busy_property proto __cdecl \
	   application: ptr GApplication,
		object: gpointer,
	      property: ptr gchar


;void
g_application_unbind_busy_property proto __cdecl \
	   application: ptr GApplication,
		object: gpointer,
	      property: ptr gchar


G_END_DECLS

endif

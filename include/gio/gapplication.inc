ifndef __G_APPLICATION_H__
define __G_APPLICATION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_APPLICATION                                  <g_application_get_type>
G_APPLICATION macro inst
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_APPLICATION, GApplication)>
  endm
G_APPLICATION_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_CAST ((class),  G_TYPE_APPLICATION, GApplicationClass)>
  endm
G_IS_APPLICATION macro inst
  exitm<G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_APPLICATION)>
  endm
G_IS_APPLICATION_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_APPLICATION)>
  endm
G_APPLICATION_GET_CLASS macro inst
  exitm<G_TYPE_INSTANCE_GET_CLASS ((inst),  G_TYPE_APPLICATION, GApplicationClass)>
  endm

;GApplicationPrivate     typedef _GApplicationPrivate

_GApplication           struct
parent_instance         GObject <>
priv                    ptr GApplicationPrivate ?
_GApplication           ends
GApplication            typedef _GApplication

_GApplicationClass      struct
parent_class            GObjectClass <>
startup                 proc :ptr
activate                proc :ptr
open                    proc :ptr, :ptr, :gint, :ptr
command_line            proc :ptr, :ptr
local_command_line      proc :ptr, :ptr, :ptr
before_emit             proc :ptr, :ptr
after_emit              proc :ptr, :ptr
add_platform_data       proc :ptr, :ptr
quit_mainloop           proc :ptr
run_mainloop            proc :ptr
shutdown                proc :ptr
dbus_register           proc :ptr, :ptr, :ptr, :ptr
dbus_unregister         proc :ptr, :ptr, :ptr
handle_local_options    proc :ptr, :ptr
name_lost               proc :ptr
padding                 gpointer 7 dup(?)
_GApplicationClass      ends
GApplicationClass       typedef _GApplicationClass

g_application_get_type proto
g_application_id_is_valid proto :ptr
g_application_new proto :ptr, :GApplicationFlags
g_application_get_application_id proto :ptr
g_application_set_application_id proto :ptr, :ptr
g_application_get_dbus_connection proto :ptr
g_application_get_dbus_object_path proto :ptr
g_application_get_inactivity_timeout proto :ptr
g_application_set_inactivity_timeout proto :ptr, :guint
g_application_get_flags proto :ptr
g_application_set_flags proto :ptr, :GApplicationFlags
g_application_get_resource_base_path proto :ptr
g_application_set_resource_base_path proto :ptr, :ptr
g_application_set_action_group proto :ptr, :ptr
g_application_add_main_option_entries proto :ptr, :ptr

g_application_add_main_option proto :ptr, :ptr, :sbyte, :GOptionFlags, :GOptionArg, :ptr, :ptr
g_application_add_option_group proto :ptr, :ptr
g_application_set_option_context_parameter_string proto :ptr, :ptr
g_application_set_option_context_summary proto :ptr, :ptr
g_application_set_option_context_description proto :ptr, :ptr
g_application_get_is_registered proto :ptr
g_application_get_is_remote proto :ptr

g_application_register proto :ptr, :ptr, :ptr
g_application_hold proto :ptr
g_application_release proto :ptr
g_application_activate proto :ptr
g_application_open proto :ptr, :ptr, :gint, :ptr
g_application_run proto :ptr, :sdword, :ptr
g_application_quit proto :ptr
g_application_get_default proto
g_application_set_default proto :ptr

g_application_mark_busy proto :ptr
g_application_unmark_busy proto :ptr
g_application_get_is_busy proto :ptr

g_application_send_notification proto :ptr, :ptr, :ptr
g_application_withdraw_notification proto :ptr, :ptr
g_application_bind_busy_property proto :ptr, :gpointer, :ptr
g_application_unbind_busy_property proto :ptr, :gpointer, :ptr

endif

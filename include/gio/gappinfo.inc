ifndef __G_APP_INFO_H__
define __G_APP_INFO_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_APP_INFO            <g_app_info_get_type>
G_APP_INFO macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_APP_INFO, GAppInfo))>
  endm
G_IS_APP_INFO macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_APP_INFO))>
  endm
G_APP_INFO_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_APP_INFO, GAppInfoIface))>
  endm

define G_TYPE_APP_LAUNCH_CONTEXT         <g_app_launch_context_get_type>
G_APP_LAUNCH_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_APP_LAUNCH_CONTEXT, GAppLaunchContext))>
  endm
G_APP_LAUNCH_CONTEXT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_APP_LAUNCH_CONTEXT, GAppLaunchContextClass))>
  endm
G_IS_APP_LAUNCH_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_APP_LAUNCH_CONTEXT))>
  endm
G_IS_APP_LAUNCH_CONTEXT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_APP_LAUNCH_CONTEXT))>
  endm
G_APP_LAUNCH_CONTEXT_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_APP_LAUNCH_CONTEXT, GAppLaunchContextClass))>
  endm

;GAppLaunchContextClass  typedef _GAppLaunchContextClass
;GAppLaunchContextPrivate typedef _GAppLaunchContextPrivate

_GAppInfoIface          struct
g_iface                 GTypeInterface <>
_dup                     proc :ptr
equal                   proc :ptr, :ptr
get_id                  proc :ptr
get_name                proc :ptr
get_description         proc :ptr
get_executable          proc :ptr
get_icon                proc :ptr
launch                  proc :ptr, :ptr, :ptr, :ptr
supports_uris           proc :ptr
supports_files          proc :ptr
launch_uris             proc :ptr, :ptr, :ptr, :ptr
should_show             proc :ptr
set_as_default_for_type proc :ptr, :ptr, :ptr
set_as_default_for_extension proc :ptr, :ptr, :ptr
add_supports_type       proc :ptr, :ptr, :ptr
can_remove_supports_type proc :ptr
remove_supports_type    proc :ptr, :ptr, :ptr
can_delete              proc :ptr
do_delete               proc :ptr
get_commandline         proc :ptr
get_display_name        proc :ptr
set_as_last_used_for_type proc :ptr, :ptr, :ptr
get_supported_types     proc :ptr
launch_uris_async       proc :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
launch_uris_finish      proc :ptr, :ptr, :ptr
_GAppInfoIface          ends
GAppInfoIface           typedef _GAppInfoIface

g_app_info_get_type proto
g_app_info_create_from_commandline proto :ptr, :ptr, :GAppInfoCreateFlags, :ptr
g_app_info_dup proto :ptr
g_app_info_equal proto :ptr, :ptr
g_app_info_get_id proto :ptr
g_app_info_get_name proto :ptr
g_app_info_get_display_name proto :ptr
g_app_info_get_description proto :ptr
g_app_info_get_executable proto :ptr
g_app_info_get_commandline proto :ptr
g_app_info_get_icon proto :ptr
g_app_info_launch proto :ptr, :ptr, :ptr, :ptr
g_app_info_supports_uris proto :ptr
g_app_info_supports_files proto :ptr
g_app_info_launch_uris proto :ptr, :ptr, :ptr, :ptr
g_app_info_launch_uris_async proto :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_app_info_launch_uris_finish proto :ptr, :ptr, :ptr

g_app_info_should_show proto :ptr

g_app_info_set_as_default_for_type proto :ptr, :ptr, :ptr
g_app_info_set_as_default_for_extension proto :ptr, :ptr, :ptr
g_app_info_add_supports_type proto :ptr, :ptr, :ptr
g_app_info_can_remove_supports_type proto :ptr
g_app_info_remove_supports_type proto :ptr, :ptr, :ptr
g_app_info_get_supported_types proto :ptr

g_app_info_can_delete proto :ptr
g_app_info_delete proto :ptr

g_app_info_set_as_last_used_for_type proto :ptr, :ptr, :ptr

g_app_info_get_all proto
g_app_info_get_all_for_type proto :ptr
g_app_info_get_recommended_for_type proto :ptr
g_app_info_get_fallback_for_type proto :ptr

g_app_info_reset_type_associations proto :ptr
g_app_info_get_default_for_type proto :ptr, :gboolean
g_app_info_get_default_for_uri_scheme proto :ptr

g_app_info_launch_default_for_uri proto :ptr, :ptr, :ptr

g_app_info_launch_default_for_uri_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_app_info_launch_default_for_uri_finish proto :ptr, :ptr



_GAppLaunchContext      struct
parent_instance         GObject <>
priv                    ptr GAppLaunchContextPrivate ?
_GAppLaunchContext      ends
GAppLaunchContext       typedef _GAppLaunchContext

_GAppLaunchContextClass struct
parent_class            GObjectClass <>
get_display             proc :ptr, :ptr, :ptr
get_startup_notify_id   proc :ptr, :ptr, :ptr
launch_failed           proc :ptr, :ptr
launched                proc :ptr, :ptr, :ptr
launch_started          proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_GAppLaunchContextClass ends
GAppLaunchContextClass  typedef _GAppLaunchContextClass

g_app_launch_context_get_type proto
g_app_launch_context_new proto

g_app_launch_context_setenv proto :ptr, :ptr, :ptr
g_app_launch_context_unsetenv proto :ptr, :ptr
g_app_launch_context_get_environment proto :ptr

g_app_launch_context_get_display proto :ptr, :ptr, :ptr
g_app_launch_context_get_startup_notify_id proto :ptr, :ptr, :ptr
g_app_launch_context_launch_failed proto :ptr, :ptr

define G_TYPE_APP_INFO_MONITOR                             <g_app_info_monitor_get_type>
G_APP_INFO_MONITOR macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_APP_INFO_MONITOR, GAppInfoMonitor))>
  endm
G_IS_APP_INFO_MONITOR macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_APP_INFO_MONITOR))>
  endm

;GAppInfoMonitor         typedef _GAppInfoMonitor

g_app_info_monitor_get_type proto
g_app_info_monitor_get proto

endif

ifndef __G_MAIN_H__
define __G_MAIN_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gpoll.inc
include glib/gslist.inc
include glib/gthread.inc

.enum GIOCondition {
  G_IO_IN   = GLIB_SYSDEF_POLLIN,
  G_IO_OUT  = GLIB_SYSDEF_POLLOUT,
  G_IO_PRI  = GLIB_SYSDEF_POLLPRI,
  G_IO_ERR  = GLIB_SYSDEF_POLLERR,
  G_IO_HUP  = GLIB_SYSDEF_POLLHUP,
  G_IO_NVAL = GLIB_SYSDEF_POLLNVAL
}

CALLBACKC(GSourceFunc, :gpointer)
CALLBACKC(GChildWatchFunc, :GPid, :gint, :gpointer)

GSource			STRUC
callback_data		gpointer ?
callback_funcs		ptr_t ?
source_funcs		ptr_t ?
ref_count		guint ?
context			ptr_t ?
priority		gint ?
flags			guint ?
source_id		guint ?
poll_fds		ptr_t ?
prev			ptr_t ?
next			ptr_t ?
name			ptr_t ?
priv			ptr_t ?
GSource			ENDS

GSourceCallbackFuncs	STRUC
ref			proc :gpointer
unref			proc :gpointer
get			proc :gpointer, :ptr, :ptr, :ptr
GSourceCallbackFuncs	ENDS

CALLBACKC(GSourceDummyMarshal)

GSourceFuncs		STRUC
prepare			proc :ptr, :ptr
check			proc :ptr
dispatch		proc :ptr, :GSourceFunc, :gpointer
finalize		proc :ptr
closure_callback	GSourceFunc ?
closure_marshal		GSourceDummyMarshal ?
GSourceFuncs		ENDS

G_PRIORITY_HIGH		equ -100
G_PRIORITY_DEFAULT	equ 0
G_PRIORITY_HIGH_IDLE	equ 100
G_PRIORITY_DEFAULT_IDLE equ 200
G_PRIORITY_LOW		equ 300
G_SOURCE_REMOVE		equ FALSE
G_SOURCE_CONTINUE	equ TRUE

g_main_context_new proto __cdecl
g_main_context_ref proto __cdecl :ptr
g_main_context_unref proto __cdecl :ptr
g_main_context_default proto __cdecl
g_main_context_iteration proto __cdecl :ptr, :gboolean
g_main_context_pending proto __cdecl :ptr

g_main_context_find_source_by_id proto __cdecl :ptr, :guint
g_main_context_find_source_by_user_data proto __cdecl :ptr, :ptr
g_main_context_find_source_by_funcs_user_data proto __cdecl :ptr, :ptr, :ptr

g_main_context_wakeup proto __cdecl :ptr
g_main_context_acquire proto __cdecl :ptr
g_main_context_release proto __cdecl :ptr
g_main_context_is_owner proto __cdecl :ptr
g_main_context_wait proto __cdecl :ptr, :ptr, :ptr
g_main_context_prepare proto __cdecl :ptr, :ptr
g_main_context_query proto __cdecl :ptr, :gint, :ptr, :ptr, :gint
g_main_context_check proto __cdecl :ptr, :gint, :ptr, :gint
g_main_context_dispatch proto __cdecl :ptr
g_main_context_set_poll_func proto __cdecl :ptr, :GPollFunc
g_main_context_get_poll_func proto __cdecl :ptr

g_main_context_add_poll proto __cdecl :ptr, :ptr, :gint
g_main_context_remove_poll proto __cdecl :ptr, :ptr
g_main_depth proto __cdecl
g_main_current_source proto __cdecl
g_main_context_push_thread_default proto __cdecl :ptr
g_main_context_pop_thread_default proto __cdecl :ptr
g_main_context_get_thread_default proto __cdecl
g_main_context_ref_thread_default proto __cdecl

g_main_loop_new proto __cdecl :ptr, :gboolean
g_main_loop_run proto __cdecl :ptr
g_main_loop_quit proto __cdecl :ptr
g_main_loop_ref proto __cdecl :ptr
g_main_loop_unref proto __cdecl :ptr
g_main_loop_is_running proto __cdecl :ptr
g_main_loop_get_context proto __cdecl :ptr

g_source_new proto __cdecl :ptr, :guint
g_source_ref proto __cdecl :ptr
g_source_unref proto __cdecl :ptr
g_source_attach proto __cdecl :ptr, :ptr
g_source_destroy proto __cdecl :ptr
g_source_set_priority proto __cdecl :ptr, :gint
g_source_get_priority proto __cdecl :ptr
g_source_set_can_recurse proto __cdecl :ptr, :gboolean
g_source_get_can_recurse proto __cdecl :ptr
g_source_get_id proto __cdecl :ptr
g_source_get_context proto __cdecl :ptr
g_source_set_callback proto __cdecl :ptr, :GSourceFunc, :gpointer, :GDestroyNotify
g_source_set_funcs proto __cdecl :ptr, :ptr
g_source_is_destroyed proto __cdecl :ptr
g_source_set_name proto __cdecl :ptr, :ptr
g_source_get_name proto __cdecl :ptr
g_source_set_name_by_id proto __cdecl :guint, :ptr
g_source_set_ready_time proto __cdecl :ptr, :gint64
g_source_get_ready_time proto __cdecl :ptr

ifdef G_OS_UNIX
g_source_add_unix_fd proto __cdecl :ptr, :gint, :GIOCondition
g_source_modify_unix_fd proto __cdecl :ptr, :gpointer, :GIOCondition
g_source_remove_unix_fd proto __cdecl :ptr, :gpointer
g_source_query_unix_fd proto __cdecl :ptr, :gpointer
endif

g_source_set_callback_indirect proto __cdecl :ptr, :ptr, :ptr
g_source_add_poll proto __cdecl :ptr, :ptr
g_source_remove_poll proto __cdecl :ptr, :ptr
g_source_add_child_source proto __cdecl :ptr, :ptr
g_source_remove_child_source proto __cdecl :ptr, :ptr
g_source_get_current_time proto __cdecl :ptr, :ptr
g_source_get_time proto __cdecl :ptr
g_source_connect_closure proto __cdecl :ptr, :ptr
g_idle_source_new proto __cdecl
g_child_watch_source_new proto __cdecl :GPid
g_timeout_source_new proto __cdecl :guint
g_timeout_source_new_seconds proto __cdecl :guint
g_get_current_time proto __cdecl :ptr
g_get_monotonic_time proto __cdecl
g_get_real_time proto __cdecl
g_source_remove proto __cdecl :guint
g_source_remove_by_user_data proto __cdecl :ptr
g_source_remove_by_funcs_user_data proto __cdecl :ptr, :ptr
g_timeout_add_full proto __cdecl :gint, :guint, :GSourceFunc, :ptr, :GDestroyNotify
g_timeout_add proto __cdecl :guint, :GSourceFunc, :ptr
g_timeout_add_seconds_full proto __cdecl :gint, :guint, :GSourceFunc, :ptr, :GDestroyNotify
g_timeout_add_seconds proto __cdecl :guint, :GSourceFunc, :ptr
g_child_watch_add_full proto __cdecl :gint, :GPid, :GChildWatchFunc, :ptr, :GDestroyNotify
g_child_watch_add proto __cdecl :GPid, :GChildWatchFunc, :ptr
g_idle_add proto __cdecl :GSourceFunc, :ptr
g_idle_add_full proto __cdecl :gint, :GSourceFunc, :ptr, :GDestroyNotify
g_idle_remove_by_data proto __cdecl :ptr
g_main_context_invoke_full proto __cdecl :ptr, :gint, :GSourceFunc, :ptr, :GDestroyNotify
g_main_context_invoke proto __cdecl :ptr, :GSourceFunc, :ptr

endif

ifndef __G_MAIN_H__
__G_MAIN_H__ equ <>
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
prepare			proc :ptr GSource, :ptr gint
check			proc :ptr GSource
dispatch		proc :ptr GSource, :GSourceFunc, :gpointer
finalize		proc :ptr GSource
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

;GMainContext
g_main_context_new proto __cdecl
;GMainContext
g_main_context_ref proto __cdecl \
	       context: ptr GMainContext

;void
g_main_context_unref proto __cdecl \
	       context: ptr GMainContext

;GMainContext
g_main_context_default proto __cdecl

;gboolean
g_main_context_iteration proto __cdecl \
	       context: ptr GMainContext,
	     may_block: gboolean

;gboolean
g_main_context_pending proto __cdecl \
	       context: ptr GMainContext


;; For implementation of legacy interfaces
;;
;GSource
g_main_context_find_source_by_id proto __cdecl \
	       context: ptr GMainContext,
	     source_id: guint

;GSource
g_main_context_find_source_by_user_data proto __cdecl \
	       context: ptr GMainContext,
	     user_data: gpointer

;GSource
g_main_context_find_source_by_funcs_user_data proto __cdecl \
	       context: ptr GMainContext,
		 funcs: ptr GSourceFuncs,
	     user_data: gpointer


;; Low level functions for implementing custom main loops.
;;
;void
g_main_context_wakeup proto __cdecl \
	       context: ptr GMainContext

;gboolean
g_main_context_acquire proto __cdecl \
	       context: ptr GMainContext

;void
g_main_context_release proto __cdecl \
	       context: ptr GMainContext

;gboolean
g_main_context_is_owner proto __cdecl \
	       context: ptr GMainContext

;gboolean
g_main_context_wait proto __cdecl \
	       context: ptr GMainContext,
		  cond: ptr GCond,
		 mutex: ptr GMutex


;gboolean
g_main_context_prepare proto __cdecl \
	       context: ptr GMainContext,
	      priority: ptr gint

;gint
g_main_context_query proto __cdecl \
	       context: ptr GMainContext,
	  max_priority: gint,
	      timeout_: ptr gint,
		   fds: ptr GPollFD,
		 n_fds: gint

;gint
g_main_context_check proto __cdecl \
	       context: ptr GMainContext,
	  max_priority: gint,
		   fds: ptr GPollFD,
		 n_fds: gint

;void
g_main_context_dispatch proto __cdecl \
	       context: ptr GMainContext


;void
g_main_context_set_poll_func proto __cdecl \
	       context: ptr GMainContext,
		  func: GPollFunc

;GPollFunc
g_main_context_get_poll_func proto __cdecl \
	       context: ptr GMainContext


;; Low level functions for use by source implementations
;;
;void
g_main_context_add_poll proto __cdecl \
	       context: ptr GMainContext,
		    fd: ptr GPollFD,
	      priority: gint

;void
g_main_context_remove_poll proto __cdecl \
	       context: ptr GMainContext,
		    fd: ptr GPollFD


;gint
g_main_depth proto __cdecl
;GSource
g_main_current_source proto __cdecl

;; GMainContexts for other threads
;;
;void
g_main_context_push_thread_default proto __cdecl \
	       context: ptr GMainContext

;void
g_main_context_pop_thread_default proto __cdecl \
	       context: ptr GMainContext

;GMainContext
g_main_context_get_thread_default proto __cdecl
;GMainContext
g_main_context_ref_thread_default proto __cdecl

;; GMainLoop:

;GMainLoop
g_main_loop_new proto __cdecl \
	       context: ptr GMainContext,
	    is_running: gboolean

;void
g_main_loop_run proto __cdecl \
		 _loop: ptr GMainLoop

;void
g_main_loop_quit proto __cdecl \
		 _loop: ptr GMainLoop

;GMainLoop
g_main_loop_ref proto __cdecl \
		 _loop: ptr GMainLoop

;void
g_main_loop_unref proto __cdecl \
		 _loop: ptr GMainLoop

;gboolean
g_main_loop_is_running proto __cdecl \
		 _loop: ptr GMainLoop

;GMainContext
g_main_loop_get_context proto __cdecl \
		 _loop: ptr GMainLoop


;; GSource:

;GSource
g_source_new proto __cdecl \
	  source_funcs: ptr GSourceFuncs,
	   struct_size: guint

;GSource
g_source_ref proto __cdecl \
		source: ptr GSource

;void
g_source_unref proto __cdecl \
		source: ptr GSource


;guint
g_source_attach proto __cdecl \
		source: ptr GSource,
	       context: ptr GMainContext

;void
g_source_destroy proto __cdecl \
		source: ptr GSource


;void
g_source_set_priority proto __cdecl \
		source: ptr GSource,
	      priority: gint

;gint
g_source_get_priority proto __cdecl \
		source: ptr GSource

;void
g_source_set_can_recurse proto __cdecl \
		source: ptr GSource,
	   can_recurse: gboolean

;gboolean
g_source_get_can_recurse proto __cdecl \
		source: ptr GSource

;guint
g_source_get_id proto __cdecl \
		source: ptr GSource


;GMainContext
g_source_get_context proto __cdecl \
		source: ptr GSource


;void
g_source_set_callback proto __cdecl \
		source: ptr GSource,
		  func: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify


;void
g_source_set_funcs proto __cdecl \
		source: ptr GSource,
		 funcs: ptr GSourceFuncs

;gboolean
g_source_is_destroyed proto __cdecl \
		source: ptr GSource


;void
g_source_set_name proto __cdecl \
		source: ptr GSource,
		  name: ptr char_t

;const
g_source_get_name proto __cdecl \
		source: ptr GSource

;void
g_source_set_name_by_id proto __cdecl \
		   tag: guint,
		  name: ptr char_t


;void
g_source_set_ready_time proto __cdecl \
		source: ptr GSource,
	    ready_time: gint64

;gint64
g_source_get_ready_time proto __cdecl \
		source: ptr GSource


ifdef G_OS_UNIX
;gpointer
g_source_add_unix_fd proto __cdecl \
		source: ptr GSource,
		    fd: gint,
		events: GIOCondition

;void
g_source_modify_unix_fd proto __cdecl \
		source: ptr GSource,
		   tag: gpointer,
	    new_events: GIOCondition

;void
g_source_remove_unix_fd proto __cdecl \
		source: ptr GSource,
		   tag: gpointer

;GIOCondition
g_source_query_unix_fd proto __cdecl \
		source: ptr GSource,
		   tag: gpointer

endif

;; Used to implement g_source_connect_closure and internally
;void
g_source_set_callback_indirect proto __cdecl \
		source: ptr GSource,
	 callback_data: gpointer,
	callback_funcs: ptr GSourceCallbackFuncs


;void
g_source_add_poll proto __cdecl \
		source: ptr GSource,
		    fd: ptr GPollFD

;void
g_source_remove_poll proto __cdecl \
		source: ptr GSource,
		    fd: ptr GPollFD


;void
g_source_add_child_source proto __cdecl \
		source: ptr GSource,
	  child_source: ptr GSource

;void
g_source_remove_child_source proto __cdecl \
		source: ptr GSource,
	  child_source: ptr GSource


;GLIB_DEPRECATED_IN_2_28_FOR(g_source_get_time)
;void
g_source_get_current_time proto __cdecl \
		source: ptr GSource,
	       timeval: ptr GTimeVal


;gint64
g_source_get_time proto __cdecl \
		source: ptr GSource


g_source_connect_closure proto __cdecl \
		source: ptr GSource,
	       closure: ptr GClosure


;GSource
g_idle_source_new proto __cdecl
g_child_watch_source_new proto __cdecl \
		   pid: GPid

g_timeout_source_new proto __cdecl \
	      interval: guint

g_timeout_source_new_seconds proto __cdecl \
	      interval: guint


g_get_current_time proto __cdecl \
		result: ptr GTimeVal

;gint64
g_get_monotonic_time proto __cdecl
;gint64
g_get_real_time proto __cdecl


;gboolean
g_source_remove proto __cdecl \
		   tag: guint

;gboolean
g_source_remove_by_user_data proto __cdecl \
	     user_data: gpointer

;gboolean
g_source_remove_by_funcs_user_data proto __cdecl \
		 funcs: ptr GSourceFuncs,
	     user_data: gpointer


;guint
g_timeout_add_full proto __cdecl \
	      priority: gint,
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
g_timeout_add proto __cdecl \
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer

;guint
g_timeout_add_seconds_full proto __cdecl \
	      priority: gint,
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
g_timeout_add_seconds proto __cdecl \
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer

;guint
g_child_watch_add_full proto __cdecl \
	      priority: gint,
		   pid: GPid,
	      function: GChildWatchFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
g_child_watch_add proto __cdecl \
		   pid: GPid,
	      function: GChildWatchFunc,
		  data: gpointer

;guint
g_idle_add proto __cdecl \
	      function: GSourceFunc,
		  data: gpointer

;guint
g_idle_add_full proto __cdecl \
	      priority: gint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;gboolean
g_idle_remove_by_data proto __cdecl \
		  data: gpointer


;void
g_main_context_invoke_full proto __cdecl \
	       context: ptr GMainContext,
	      priority: gint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;void
g_main_context_invoke proto __cdecl \
	       context: ptr GMainContext,
	      function: GSourceFunc,
		  data: gpointer


;GLIB_VAR GSourceFuncs g_timeout_funcs;
;GLIB_VAR GSourceFuncs g_child_watch_funcs;
;GLIB_VAR GSourceFuncs g_idle_funcs;
ifdef G_OS_UNIX
;GLIB_VAR GSourceFuncs g_unix_signal_funcs;
;GLIB_VAR GSourceFuncs g_unix_fd_source_funcs;
endif

endif

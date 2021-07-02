ifndef __GDK_THREADS_H__
__GDK_THREADS_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

if defined(GDK_COMPILATION) OR defined(GTK_COMPILATION)
GDK_THREADS_DEPRECATED	equ _GDK_EXTERN
else
GDK_THREADS_DEPRECATED	equ GDK_DEPRECATED_IN_3_6
endif

gdk_threads_init proto __cdecl
gdk_threads_enter proto __cdecl
gdk_threads_leave proto __cdecl
gdk_threads_set_lock_functions proto __cdecl \
	      enter_fn: GCallback,
	      leave_fn: GCallback


;guint
gdk_threads_add_idle_full proto __cdecl \
	      priority: gint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
gdk_threads_add_idle proto __cdecl \
	      function: GSourceFunc,
		  data: gpointer

;guint
gdk_threads_add_timeout_full proto __cdecl \
	      priority: gint,
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
gdk_threads_add_timeout proto __cdecl \
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer

;guint
gdk_threads_add_timeout_seconds_full proto __cdecl \
	      priority: gint,
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer,
		notify: GDestroyNotify

;guint
gdk_threads_add_timeout_seconds proto __cdecl \
	      interval: guint,
	      function: GSourceFunc,
		  data: gpointer


GDK_THREADS_ENTER macro
	exitm<gdk_threads_enter()>
	endm

GDK_THREADS_LEAVE macro
	exitm<gdk_threads_leave()>
	endm

undef GDK_THREADS_DEPRECATED

endif

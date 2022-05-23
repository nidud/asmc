ifndef __G_THREAD_H__
__G_THREAD_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gatomic.inc
include glib/gerror.inc
include glib/gutils.inc

.enum GThreadError {
  G_THREAD_ERROR_AGAIN
}

CALLBACKC(GThreadFunc, :gpointer)

G_THREAD_ERROR		equ <g_thread_error_quark>

g_thread_error_quark proto __cdecl

G_THREAD_ERROR_AGAIN	equ 0

GMutex			UNION
p			gpointer ?
i			guint 2 dup(?)
GMutex			ENDS

GRWLock			STRUC
p			gpointer ?
i			guint 2 dup(?)
GRWLock			ENDS

GCond			STRUC
p			gpointer ?
i			guint 2 dup(?)
GCond			ENDS

GRecMutex		STRUC
p			gpointer ?
i			guint 2 dup(?)
GRecMutex		ENDS

G_PRIVATE_INIT macro notify
	exitm<{ NULL, (notify), { NULL, NULL } }>
	endm

GPrivate		STRUC
p			gpointer ?
notify			GDestroyNotify ?
future			gpointer 2 dup(?)
GPrivate		ENDS

.enum GOnceStatus {
  G_ONCE_STATUS_NOTCALLED,
  G_ONCE_STATUS_PROGRESS,
  G_ONCE_STATUS_READY
}

G_ONCE_INIT		equ <{ G_ONCE_STATUS_NOTCALLED, NULL }>

GOnce			STRUC
status			GOnceStatus ?
retval			gpointer ?
GOnce			ENDS

G_LOCK_NAME macro name
	exitm<g__&name&_lock>
	endm
G_LOCK_DEFINE_STATIC macro name
	exitm<static G_LOCK_DEFINE (name)>
	endm
G_LOCK_DEFINE macro name
	exitm<GMutex G_LOCK_NAME (name)>
	endm
G_LOCK_EXTERN macro name
	exitm<extern GMutex G_LOCK_NAME (name)>
	endm

ifdef G_DEBUG_LOCKS
else
endif

;GThread
g_thread_ref proto __cdecl \
		thread: ptr GThread

g_thread_unref proto __cdecl \
		thread: ptr GThread

g_thread_new proto __cdecl \
		  name: ptr gchar,
		  func: GThreadFunc,
		  data: gpointer

g_thread_try_new proto __cdecl \
		  name: ptr gchar,
		  func: GThreadFunc,
		  data: gpointer,
		 error: ptr GError

g_thread_self proto __cdecl

g_thread_exit proto __cdecl \
		retval: gpointer

;gpointer
g_thread_join proto __cdecl \
		thread: ptr GThread

g_thread_yield proto __cdecl

g_mutex_init proto __cdecl \
		 mutex: ptr GMutex

g_mutex_clear proto __cdecl \
		 mutex: ptr GMutex

g_mutex_lock proto __cdecl \
		 mutex: ptr GMutex

;gboolean
g_mutex_trylock proto __cdecl \
		 mutex: ptr GMutex

g_mutex_unlock proto __cdecl \
		 mutex: ptr GMutex

g_rw_lock_init proto __cdecl \
	       rw_lock: ptr GRWLock

g_rw_lock_clear proto __cdecl \
	       rw_lock: ptr GRWLock

g_rw_lock_writer_lock proto __cdecl \
	       rw_lock: ptr GRWLock

;gboolean
g_rw_lock_writer_trylock proto __cdecl \
	       rw_lock: ptr GRWLock

g_rw_lock_writer_unlock proto __cdecl \
	       rw_lock: ptr GRWLock

g_rw_lock_reader_lock proto __cdecl \
	       rw_lock: ptr GRWLock

;gboolean
g_rw_lock_reader_trylock proto __cdecl \
	       rw_lock: ptr GRWLock

g_rw_lock_reader_unlock proto __cdecl \
	       rw_lock: ptr GRWLock

g_rec_mutex_init proto __cdecl \
	     rec_mutex: ptr GRecMutex

g_rec_mutex_clear proto __cdecl \
	     rec_mutex: ptr GRecMutex

g_rec_mutex_lock proto __cdecl \
	     rec_mutex: ptr GRecMutex

;gboolean
g_rec_mutex_trylock proto __cdecl \
	     rec_mutex: ptr GRecMutex

g_rec_mutex_unlock proto __cdecl \
	     rec_mutex: ptr GRecMutex

g_cond_init proto __cdecl \
		  cond: ptr GCond

g_cond_clear proto __cdecl \
		  cond: ptr GCond

g_cond_wait proto __cdecl \
		  cond: ptr GCond,
		 mutex: ptr GMutex

g_cond_signal proto __cdecl \
		  cond: ptr GCond

g_cond_broadcast proto __cdecl \
		  cond: ptr GCond

;gboolean
g_cond_wait_until proto __cdecl \
		  cond: ptr GCond,
		 mutex: ptr GMutex,
	      end_time: gint64

;gpointer
g_private_get proto __cdecl \
		   key: ptr GPrivate

g_private_set proto __cdecl \
		   key: ptr GPrivate,
		 value: gpointer

g_private_replace proto __cdecl \
		   key: ptr GPrivate,
		 value: gpointer


;gpointer
g_once_impl proto __cdecl \
		  once: ptr GOnce,
		  func: GThreadFunc,
		   arg: gpointer

;gboolean
g_once_init_enter proto __cdecl \
	      location: ptr

g_once_init_leave proto __cdecl \
	      location: ptr,
		result: gsize


ifdef G_ATOMIC_OP_MEMORY_BARRIER_NEEDED
else
endif

ifdef __GNUC__
else
endif

;guint
g_get_num_processors proto __cdecl

GMutexLocker		equ <>

endif

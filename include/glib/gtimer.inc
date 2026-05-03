ifndef __G_TIMER_H__
define __G_TIMER_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

define G_USEC_PER_SEC 1000000

g_timer_new proto
g_timer_destroy proto :ptr
g_timer_start proto :ptr
g_timer_stop proto :ptr
g_timer_reset proto :ptr
g_timer_continue proto :ptr
g_timer_elapsed proto :ptr, :ptr
g_timer_is_active proto :ptr

g_usleep proto :gulong

g_time_val_add proto :ptr, :glong
g_time_val_from_iso8601 proto :ptr, :ptr
g_time_val_to_iso8601 proto :ptr

endif

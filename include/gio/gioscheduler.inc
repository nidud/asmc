ifndef __G_IO_SCHEDULER_H__
define __G_IO_SCHEDULER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

g_io_scheduler_push_job proto :GIOSchedulerJobFunc, :gpointer, :GDestroyNotify, :gint, :ptr
g_io_scheduler_cancel_all_jobs proto
g_io_scheduler_job_send_to_mainloop proto :ptr, :GSourceFunc, :gpointer, :GDestroyNotify
g_io_scheduler_job_send_to_mainloop_async proto :ptr, :GSourceFunc, :gpointer, :GDestroyNotify


endif

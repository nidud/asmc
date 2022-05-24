ifndef __G_TASK_H__
define __G_TASK_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TASK         <g_task_get_type ()>
G_TASK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_TASK, GTask))>
  endm
G_TASK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_TASK, GTaskClass))>
  endm
G_IS_TASK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_TASK))>
  endm
G_IS_TASK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_TASK))>
  endm
G_TASK_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_TASK, GTaskClass))>
  endm

;GTaskClass              typedef _GTaskClass

g_task_get_type proto
g_task_new proto :gpointer, :ptr, :GAsyncReadyCallback, :gpointer
g_task_report_error proto :gpointer, :GAsyncReadyCallback, :gpointer, :gpointer, :ptr

g_task_set_task_data proto :ptr, :gpointer, :GDestroyNotify
g_task_set_priority proto :ptr, :gint
g_task_set_check_cancellable proto :ptr, :gboolean
g_task_set_source_tag proto :ptr, :gpointer
g_task_set_name proto :ptr, :ptr

if GLIB_VERSION_MIN_REQUIRED ge GLIB_VERSION_2_60
g_task_set_source_tag macro task, tag
  exitm<.err>
  endm
endif

g_task_get_source_object proto :ptr
g_task_get_task_data proto :ptr
g_task_get_priority proto :ptr
g_task_get_context proto :ptr
g_task_get_cancellable proto :ptr
g_task_get_check_cancellable proto :ptr
g_task_get_source_tag proto :ptr
g_task_get_name proto :ptr

g_task_is_valid proto :gpointer, :gpointer

CALLBACK(GTaskThreadFunc, :ptr, :gpointer, :gpointer, :ptr)

g_task_run_in_thread proto :ptr, :GTaskThreadFunc
g_task_run_in_thread_sync proto :ptr, :GTaskThreadFunc
g_task_set_return_on_cancel proto :ptr, :gboolean
g_task_get_return_on_cancel proto :ptr
g_task_attach_source proto :ptr, :ptr, :GSourceFunc
g_task_return_pointer proto :ptr, :gpointer, :GDestroyNotify
g_task_return_boolean proto :ptr, :gboolean
g_task_return_int proto :ptr, :gssize
g_task_return_error proto :ptr, :ptr
g_task_return_value proto :ptr, :ptr
g_task_return_error_if_cancelled proto :ptr
g_task_propagate_pointer proto :ptr, :ptr
g_task_propagate_boolean proto :ptr, :ptr
g_task_propagate_int proto :ptr, :ptr
g_task_propagate_value proto :ptr, :ptr, :ptr
g_task_had_error proto :ptr
g_task_get_completed proto :ptr

endif

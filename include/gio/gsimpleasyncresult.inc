ifndef __G_SIMPLE_ASYNC_RESULT_H__
define __G_SIMPLE_ASYNC_RESULT_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SIMPLE_ASYNC_RESULT         <g_simple_async_result_get_type ()>
G_SIMPLE_ASYNC_RESULT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SIMPLE_ASYNC_RESULT, GSimpleAsyncResult))>
  endm
G_SIMPLE_ASYNC_RESULT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_SIMPLE_ASYNC_RESULT, GSimpleAsyncResultClass))>
  endm
G_IS_SIMPLE_ASYNC_RESULT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SIMPLE_ASYNC_RESULT))>
  endm
G_IS_SIMPLE_ASYNC_RESULT_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_SIMPLE_ASYNC_RESULT))>
  endm
G_SIMPLE_ASYNC_RESULT_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_SIMPLE_ASYNC_RESULT, GSimpleAsyncResultClass))>
  endm


g_simple_async_result_get_type proto

g_simple_async_result_new proto :ptr, :GAsyncReadyCallback, :gpointer, :gpointer
g_simple_async_result_new_from_error proto :ptr, :GAsyncReadyCallback, :gpointer, :ptr
g_simple_async_result_new_take_error proto :ptr, :GAsyncReadyCallback, :gpointer, :ptr
g_simple_async_result_set_op_res_gpointer proto :ptr, :gpointer, :GDestroyNotify
g_simple_async_result_get_op_res_gpointer proto :ptr

g_simple_async_result_set_op_res_gssize proto :ptr, :gssize
g_simple_async_result_get_op_res_gssize proto :ptr

g_simple_async_result_set_op_res_gboolean proto :ptr, :gboolean
g_simple_async_result_get_op_res_gboolean proto :ptr

g_simple_async_result_set_check_cancellable proto :ptr, :ptr
g_simple_async_result_get_source_tag proto :ptr
g_simple_async_result_set_handle_cancellation proto :ptr, :gboolean
g_simple_async_result_complete proto :ptr
g_simple_async_result_complete_in_idle proto :ptr
g_simple_async_result_run_in_thread proto :ptr, :GSimpleAsyncThreadFunc, :sdword, :ptr
g_simple_async_result_set_from_error proto :ptr, :ptr
g_simple_async_result_take_error proto :ptr, :ptr
g_simple_async_result_propagate_error proto :ptr, :ptr

g_simple_async_result_is_valid proto :ptr, :ptr, :gpointer

g_simple_async_report_gerror_in_idle proto :ptr, :GAsyncReadyCallback, :gpointer, :ptr
g_simple_async_report_take_gerror_in_idle proto :ptr, :GAsyncReadyCallback, :gpointer, :ptr

endif

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

ifndef __G_SUBPROCESS_H__
define __G_SUBPROCESS_H__

include gio/giotypes.inc

define G_TYPE_SUBPROCESS         <g_subprocess_get_type ()>
G_SUBPROCESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SUBPROCESS, GSubprocess))>
  endm
G_IS_SUBPROCESS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SUBPROCESS))>
  endm

g_subprocess_get_type proto
g_subprocess_new proto :GSubprocessFlags, :ptr, :ptr, :vararg
g_subprocess_newv proto :ptr, :GSubprocessFlags, :ptr
g_subprocess_get_stdin_pipe proto :ptr
g_subprocess_get_stdout_pipe proto :ptr
g_subprocess_get_stderr_pipe proto :ptr
g_subprocess_get_identifier proto :ptr

ifdef G_OS_UNIX
g_subprocess_send_signal proto :ptr, :gint
endif

g_subprocess_force_exit proto :ptr
g_subprocess_wait proto :ptr, :ptr, :ptr
g_subprocess_wait_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_subprocess_wait_finish proto :ptr, :ptr, :ptr
g_subprocess_wait_check proto :ptr, :ptr, :ptr
g_subprocess_wait_check_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_subprocess_wait_check_finish proto :ptr, :ptr, :ptr
g_subprocess_get_status proto :ptr
g_subprocess_get_successful proto :ptr
g_subprocess_get_if_exited proto :ptr
g_subprocess_get_exit_status proto :ptr
g_subprocess_get_if_signaled proto :ptr
g_subprocess_get_term_sig proto :ptr
g_subprocess_communicate proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_subprocess_communicate_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_subprocess_communicate_finish proto :ptr, :ptr, :ptr, :ptr, :ptr
g_subprocess_communicate_utf8 proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_subprocess_communicate_utf8_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_subprocess_communicate_utf8_finish proto :ptr, :ptr, :ptr, :ptr, :ptr

endif

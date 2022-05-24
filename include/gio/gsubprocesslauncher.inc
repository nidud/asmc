if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

ifndef __G_SUBPROCESS_LAUNCHER_H__
define __G_SUBPROCESS_LAUNCHER_H__

include gio/giotypes.inc

define G_TYPE_SUBPROCESS_LAUNCHER         <g_subprocess_launcher_get_type ()>
G_SUBPROCESS_LAUNCHER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_SUBPROCESS_LAUNCHER, GSubprocessLauncher))>
  endm
G_IS_SUBPROCESS_LAUNCHER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_SUBPROCESS_LAUNCHER))>
  endm

g_subprocess_launcher_get_type proto
g_subprocess_launcher_new proto :GSubprocessFlags
g_subprocess_launcher_spawn proto :ptr, :ptr, :ptr, :vararg
g_subprocess_launcher_spawnv proto :ptr, :ptr, :ptr
g_subprocess_launcher_set_environ proto :ptr, :ptr
g_subprocess_launcher_setenv proto :ptr, :ptr, :ptr, :gboolean
g_subprocess_launcher_unsetenv proto :ptr, :ptr
g_subprocess_launcher_getenv proto :ptr, :ptr
g_subprocess_launcher_set_cwd proto :ptr, :ptr
g_subprocess_launcher_set_flags proto :ptr, :GSubprocessFlags


ifdef G_OS_UNIX
g_subprocess_launcher_set_stdin_file_path proto :ptr, :ptr
g_subprocess_launcher_take_stdin_fd proto :ptr, :gint
g_subprocess_launcher_set_stdout_file_path proto :ptr, :ptr
g_subprocess_launcher_take_stdout_fd proto :ptr, :gint
g_subprocess_launcher_set_stderr_file_path proto :ptr, :ptr
g_subprocess_launcher_take_stderr_fd proto :ptr, :gint
g_subprocess_launcher_take_fd proto :ptr, :gint, :gint
g_subprocess_launcher_close proto :ptr
g_subprocess_launcher_set_child_setup proto :ptr, :GSpawnChildSetupFunc, :gpointer, :GDestroyNotify
endif

endif

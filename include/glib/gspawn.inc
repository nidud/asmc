ifndef __G_SPAWN_H__
define __G_SPAWN_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc

define G_SPAWN_ERROR (g_spawn_error_quark ())

.enum GSpawnError {
  G_SPAWN_ERROR_FORK,
  G_SPAWN_ERROR_READ,
  G_SPAWN_ERROR_CHDIR,
  G_SPAWN_ERROR_ACCES,
  G_SPAWN_ERROR_PERM,
  G_SPAWN_ERROR_TOO_BIG,
  G_SPAWN_ERROR_2BIG = G_SPAWN_ERROR_TOO_BIG,
  G_SPAWN_ERROR_NOEXEC,
  G_SPAWN_ERROR_NAMETOOLONG,
  G_SPAWN_ERROR_NOENT,
  G_SPAWN_ERROR_NOMEM,
  G_SPAWN_ERROR_NOTDIR,
  G_SPAWN_ERROR_LOOP,
  G_SPAWN_ERROR_TXTBUSY,
  G_SPAWN_ERROR_IO,
  G_SPAWN_ERROR_NFILE,
  G_SPAWN_ERROR_MFILE,
  G_SPAWN_ERROR_INVAL,
  G_SPAWN_ERROR_ISDIR,
  G_SPAWN_ERROR_LIBBAD,

}


define G_SPAWN_EXIT_ERROR (g_spawn_exit_error_quark ())


CALLBACK(GSpawnChildSetupFunc, :gpointer)


.enum GSpawnFlags {
  G_SPAWN_DEFAULT                = 0,
  G_SPAWN_LEAVE_DESCRIPTORS_OPEN = 1 shl 0,
  G_SPAWN_DO_NOT_REAP_CHILD      = 1 shl 1,

  G_SPAWN_SEARCH_PATH            = 1 shl 2,

  G_SPAWN_STDOUT_TO_DEV_NULL     = 1 shl 3,
  G_SPAWN_STDERR_TO_DEV_NULL     = 1 shl 4,
  G_SPAWN_CHILD_INHERITS_STDIN   = 1 shl 5,
  G_SPAWN_FILE_AND_ARGV_ZERO     = 1 shl 6,
  G_SPAWN_SEARCH_PATH_FROM_ENVP  = 1 shl 7,
  G_SPAWN_CLOEXEC_PIPES          = 1 shl 8
}

g_spawn_error_quark proto
g_spawn_exit_error_quark proto

g_spawn_async proto :ptr, :ptr, :ptr, :GSpawnFlags, :GSpawnChildSetupFunc, :gpointer, :ptr, :ptr
g_spawn_async_with_pipes proto :ptr, :ptr, :ptr, :GSpawnFlags, :GSpawnChildSetupFunc, :gpointer, :ptr, :ptr, :ptr, :ptr, :ptr
g_spawn_async_with_pipes_and_fds proto :ptr, :ptr, :ptr, :GSpawnFlags, :GSpawnChildSetupFunc, :gpointer, :gint, :gint, :gint, :ptr, :ptr, :gsize, :ptr, :ptr, :ptr, :ptr, :ptr
g_spawn_async_with_fds proto :ptr, :ptr, :ptr, :GSpawnFlags, :GSpawnChildSetupFunc, :gpointer, :ptr, :gint, :gint, :gint, :ptr
g_spawn_sync proto :ptr, :ptr, :ptr, :GSpawnFlags, :GSpawnChildSetupFunc, :gpointer, :ptr, :ptr, :ptr, :ptr
g_spawn_command_line_sync proto :ptr, :ptr, :ptr, :ptr, :ptr
g_spawn_command_line_async proto :ptr, :ptr
g_spawn_check_wait_status proto :gint, :ptr
g_spawn_check_exit_status proto :gint, :ptr
g_spawn_close_pid proto :GPid

endif

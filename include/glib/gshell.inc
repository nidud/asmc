ifndef __G_SHELL_H__
define __G_SHELL_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc

define G_SHELL_ERROR <g_shell_error_quark>

.enum GShellError {

  G_SHELL_ERROR_BAD_QUOTING,

  G_SHELL_ERROR_EMPTY_STRING,
  G_SHELL_ERROR_FAILED
}

g_shell_error_quark proto

g_shell_quote proto :ptr
g_shell_unquote proto :ptr, :ptr
g_shell_parse_argv proto :ptr, :ptr, :ptr, :ptr

endif

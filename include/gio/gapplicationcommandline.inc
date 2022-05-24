ifndef __G_APPLICATION_COMMAND_LINE_H__
define __G_APPLICATION_COMMAND_LINE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc


define G_TYPE_APPLICATION_COMMAND_LINE                     <g_application_command_line_get_type ()>
G_APPLICATION_COMMAND_LINE macro inst
  exitm<G_TYPE_CHECK_INSTANCE_CAST (inst, G_TYPE_APPLICATION_COMMAND_LINE, GApplicationCommandLine)>
  endm
G_APPLICATION_COMMAND_LINE_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_CAST (class, G_TYPE_APPLICATION_COMMAND_LINE, GApplicationCommandLineClass)>
  endm
G_IS_APPLICATION_COMMAND_LINE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_APPLICATION_COMMAND_LINE))>
  endm
G_IS_APPLICATION_COMMAND_LINE_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_APPLICATION_COMMAND_LINE))>
  endm
G_APPLICATION_COMMAND_LINE_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_APPLICATION_COMMAND_LINE, GApplicationCommandLineClass))>
  endm

;GApplicationCommandLinePrivate typedef _GApplicationCommandLinePrivate

_GApplicationCommandLine struct
parent_instance         GObject <>
priv                    ptr GApplicationCommandLinePrivate ?
_GApplicationCommandLine ends
GApplicationCommandLine typedef _GApplicationCommandLine

_GApplicationCommandLineClass struct
parent_class            GObjectClass <>
print_literal           proc :ptr, :ptr
printerr_literal        proc :ptr, :ptr
get_stdin               proc :ptr
padding                 gpointer 11 dup(?)
_GApplicationCommandLineClass ends
GApplicationCommandLineClass typedef _GApplicationCommandLineClass

g_application_command_line_get_type proto
g_application_command_line_get_arguments proto :ptr, :ptr
g_application_command_line_get_options_dict proto :ptr
g_application_command_line_get_stdin proto :ptr
g_application_command_line_get_environ proto :ptr
g_application_command_line_getenv proto :ptr, :ptr
g_application_command_line_get_cwd proto :ptr
g_application_command_line_get_is_remote proto :ptr

g_application_command_line_get_exit_status proto :ptr
g_application_command_line_set_exit_status proto :ptr, :sdword
g_application_command_line_get_platform_data proto :ptr
g_application_command_line_create_file_for_arg proto :ptr, :ptr

endif

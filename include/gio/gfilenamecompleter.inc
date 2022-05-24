ifndef __G_FILENAME_COMPLETER_H__
define __G_FILENAME_COMPLETER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILENAME_COMPLETER         <g_filename_completer_get_type ()>
G_FILENAME_COMPLETER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILENAME_COMPLETER, GFilenameCompleter))>
  endm
G_FILENAME_COMPLETER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILENAME_COMPLETER, GFilenameCompleterClass))>
  endm
G_FILENAME_COMPLETER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILENAME_COMPLETER, GFilenameCompleterClass))>
  endm
G_IS_FILENAME_COMPLETER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILENAME_COMPLETER))>
  endm
G_IS_FILENAME_COMPLETER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILENAME_COMPLETER))>
  endm


_GFilenameCompleterClass struct
parent_class            GObjectClass <>
got_completion_data     proc :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_GFilenameCompleterClass ends
GFilenameCompleterClass typedef _GFilenameCompleterClass

g_filename_completer_get_type proto
g_filename_completer_new proto
g_filename_completer_get_completion_suffix proto :ptr, :ptr
g_filename_completer_get_completions proto :ptr, :ptr
g_filename_completer_set_dirs_only proto :ptr, :gboolean

endif

ifndef __G_FILE_ENUMERATOR_H__
define __G_FILE_ENUMERATOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILE_ENUMERATOR         <g_file_enumerator_get_type ()>
G_FILE_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_ENUMERATOR, GFileEnumerator))>
  endm
G_FILE_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_ENUMERATOR, GFileEnumeratorClass))>
  endm
G_IS_FILE_ENUMERATOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_ENUMERATOR))>
  endm
G_IS_FILE_ENUMERATOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_ENUMERATOR))>
  endm
G_FILE_ENUMERATOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_ENUMERATOR, GFileEnumeratorClass))>
  endm


GFileEnumerator         struct
parent_instance         GObject <>
priv                    ptr GFileEnumeratorPrivate ?
GFileEnumerator         ends

GFileEnumeratorClass    struct
parent_class            GObjectClass <>
next_file               proc :ptr, :ptr, :ptr
close_fn                proc :ptr, :ptr, :ptr
next_files_async        proc :ptr, :sdword, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
next_files_finish       proc :ptr, :ptr, :ptr
close_async             proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
close_finish            proc :ptr, :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
GFileEnumeratorClass    ends

g_file_enumerator_get_type proto

g_file_enumerator_next_file proto :ptr, :ptr, :ptr
g_file_enumerator_close proto :ptr, :ptr, :ptr
g_file_enumerator_next_files_async proto :ptr, :sdword, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_file_enumerator_next_files_finish proto :ptr, :ptr, :ptr
g_file_enumerator_close_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_file_enumerator_close_finish proto :ptr, :ptr, :ptr
g_file_enumerator_is_closed proto :ptr
g_file_enumerator_has_pending proto :ptr
g_file_enumerator_set_pending proto :ptr, :gboolean
g_file_enumerator_get_container proto :ptr
g_file_enumerator_get_child proto :ptr, :ptr

g_file_enumerator_iterate proto :ptr, :ptr, :ptr, :ptr, :ptr

endif

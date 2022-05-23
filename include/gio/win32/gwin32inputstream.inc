ifndef __G_WIN32_INPUT_STREAM_H__
define __G_WIN32_INPUT_STREAM_H__

include gio/gio.inc

define G_TYPE_WIN32_INPUT_STREAM         <g_win32_input_stream_get_type>
G_WIN32_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_WIN32_INPUT_STREAM, GWin32InputStream))>
  endm
G_WIN32_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_WIN32_INPUT_STREAM, GWin32InputStreamClass))>
  endm
G_IS_WIN32_INPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_WIN32_INPUT_STREAM))>
  endm
G_IS_WIN32_INPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_WIN32_INPUT_STREAM))>
  endm
G_WIN32_INPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_WIN32_INPUT_STREAM, GWin32InputStreamClass))>
  endm

;GWin32InputStreamPrivate typedef _GWin32InputStreamPrivate

_GWin32InputStream      struct
parent_instance         GInputStream <>
priv                    ptr GWin32InputStreamPrivate ?
_GWin32InputStream      ends
GWin32InputStream       typedef _GWin32InputStream

_GWin32InputStreamClass struct
parent_class            GInputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GWin32InputStreamClass ends
GWin32InputStreamClass  typedef _GWin32InputStreamClass

g_win32_input_stream_get_type proto

g_win32_input_stream_new proto :ptr, :gboolean
g_win32_input_stream_set_close_handle proto :ptr, :gboolean
g_win32_input_stream_get_close_handle proto :ptr
g_win32_input_stream_get_handle proto :ptr

endif

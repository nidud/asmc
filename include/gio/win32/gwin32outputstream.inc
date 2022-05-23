ifndef __G_WIN32_OUTPUT_STREAM_H__
define __G_WIN32_OUTPUT_STREAM_H__

include gio/gio.inc

define G_TYPE_WIN32_OUTPUT_STREAM         <g_win32_output_stream_get_type>
G_WIN32_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_WIN32_OUTPUT_STREAM, GWin32OutputStream))>
  endm
G_WIN32_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_WIN32_OUTPUT_STREAM, GWin32OutputStreamClass))>
  endm
G_IS_WIN32_OUTPUT_STREAM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_WIN32_OUTPUT_STREAM))>
  endm
G_IS_WIN32_OUTPUT_STREAM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_WIN32_OUTPUT_STREAM))>
  endm
G_WIN32_OUTPUT_STREAM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_WIN32_OUTPUT_STREAM, GWin32OutputStreamClass))>
  endm


;GWin32OutputStreamPrivate typedef _GWin32OutputStreamPrivate

_GWin32OutputStream     struct
parent_instance         GOutputStream <>
priv                    ptr GWin32OutputStreamPrivate ?
_GWin32OutputStream     ends
GWin32OutputStream      typedef _GWin32OutputStream

_GWin32OutputStreamClass struct
parent_class            GOutputStreamClass <>
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GWin32OutputStreamClass ends
GWin32OutputStreamClass typedef _GWin32OutputStreamClass

g_win32_output_stream_get_type proto

g_win32_output_stream_new proto :ptr, :gboolean
g_win32_output_stream_set_close_handle proto :ptr, :gboolean
g_win32_output_stream_get_close_handle proto :ptr
g_win32_output_stream_get_handle proto :ptr

endif

ifndef __G_IOCHANNEL_H__
define __G_IOCHANNEL_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gconvert.inc
include glib/gmain.inc
include glib/gstring.inc

.enum GIOError {
    G_IO_ERROR_NONE,
    G_IO_ERROR_AGAIN,
    G_IO_ERROR_INVAL,
    G_IO_ERROR_UNKNOWN
    }

G_IO_CHANNEL_ERROR equ (g_io_channel_error_quark ())

.enum GIOChannelError {
    G_IO_CHANNEL_ERROR_FBIG,
    G_IO_CHANNEL_ERROR_INVAL,
    G_IO_CHANNEL_ERROR_IO,
    G_IO_CHANNEL_ERROR_ISDIR,
    G_IO_CHANNEL_ERROR_NOSPC,
    G_IO_CHANNEL_ERROR_NXIO,
    G_IO_CHANNEL_ERROR_OVERFLOW,
    G_IO_CHANNEL_ERROR_PIPE,
    G_IO_CHANNEL_ERROR_FAILED
    }

.enum GIOStatus {
    G_IO_STATUS_ERROR,
    G_IO_STATUS_NORMAL,
    G_IO_STATUS_EOF,
    G_IO_STATUS_AGAIN
    }

.enum GSeekType {
    G_SEEK_CUR,
    G_SEEK_SET,
    G_SEEK_END
    }

.enum GIOFlags {
    G_IO_FLAG_APPEND = 1 shl 0,
    G_IO_FLAG_NONBLOCK = 1 shl 1,
    G_IO_FLAG_IS_READABLE = 1 shl 2,
    G_IO_FLAG_IS_WRITABLE = 1 shl 3,
    G_IO_FLAG_IS_WRITEABLE = 1 shl 3,
    G_IO_FLAG_IS_SEEKABLE = 1 shl 4,
    G_IO_FLAG_MASK = (1 shl 5) - 1,
    G_IO_FLAG_GET_MASK = G_IO_FLAG_MASK,
    G_IO_FLAG_SET_MASK = G_IO_FLAG_APPEND or G_IO_FLAG_NONBLOCK
    }

GIOChannel		STRUC
ref_count		gint ?
funcs			ptr_t ?
encoding		ptr_t ?
read_cd			ptr_t ?
write_cd		ptr_t ?
line_term		ptr_t ?
line_term_len		guint ?
buf_size		gsize ?
read_buf		ptr_t ?
encoded_read_buf	ptr_t ?
write_buf		ptr_t ?
partial_write_buf	gchar 6 dup(?)
RECORD
use_buffer		guint : 1 ?
do_encode		guint : 1 ?
close_on_unref		guint : 1 ?
is_readable		guint : 1 ?
is_writeable		guint : 1 ?
is_seekable		guint : 1 ?
ENDS
reserved1		gpointer ?
reserved2		gpointer ?
GIOChannel		ENDS

CALLBACKC(GIOFunc, :ptr, :GIOCondition, :gpointer)

GIOFuncs		STRUC
io_read			proc :ptr, :ptr, :gsize, :ptr, :ptr
io_write		proc :ptr, :ptr, :gsize, :ptr, :ptr
io_seek			proc :ptr, :gint64, :GSeekType, :ptr
io_close		proc :ptr, :ptr
io_create_watch		proc :ptr, :GIOCondition
io_free			proc :ptr
io_set_flags		proc :ptr, :GIOFlags, :ptr
io_get_flags		proc :ptr
GIOFuncs		ENDS

g_io_channel_init proto __cdecl :ptr
g_io_channel_ref proto __cdecl :ptr
g_io_channel_unref proto __cdecl :ptr
g_io_channel_read proto __cdecl :ptr, :ptr, :gsize, :ptr
g_io_channel_write proto __cdecl :ptr, :ptr, :gsize, :ptr
g_io_channel_seek proto __cdecl :ptr, :gint64, :GSeekType
g_io_channel_close proto __cdecl :ptr
g_io_channel_shutdown proto __cdecl :ptr, :gboolean, :ptr
g_io_add_watch_full proto __cdecl :ptr, :gint, :GIOCondition, :GIOFunc, :gpointer, :GDestroyNotify
g_io_create_watch proto __cdecl :ptr, :GIOCondition
g_io_add_watch proto __cdecl :ptr, :GIOCondition, :GIOFunc, :gpointer
g_io_channel_set_buffer_size proto __cdecl :ptr, :gsize
g_io_channel_get_buffer_size proto __cdecl :ptr
g_io_channel_get_buffer_condition proto __cdecl :ptr
g_io_channel_set_flags proto __cdecl :ptr, :GIOFlags, :ptr
g_io_channel_get_flags proto __cdecl :ptr
g_io_channel_set_line_term proto __cdecl :ptr, :ptr, :gint
g_io_channel_get_line_term proto __cdecl :ptr, :ptr
g_io_channel_set_buffered proto __cdecl :ptr, :gboolean
g_io_channel_get_buffered proto __cdecl :ptr
g_io_channel_set_encoding proto __cdecl :ptr, :ptr, :ptr
g_io_channel_get_encoding proto __cdecl :ptr
g_io_channel_set_close_on_unref proto __cdecl :ptr, :gboolean
g_io_channel_get_close_on_unref proto __cdecl :ptr

g_io_channel_flush proto __cdecl :ptr, :ptr
g_io_channel_read_line proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_io_channel_read_line_string proto __cdecl :ptr, :ptr, :ptr, :ptr
g_io_channel_read_to_end proto __cdecl :ptr, :ptr, :ptr, :ptr
g_io_channel_read_chars proto __cdecl :ptr, :ptr, :gsize, :ptr, :ptr
g_io_channel_read_unichar proto __cdecl :ptr, :ptr, :ptr
g_io_channel_write_chars proto __cdecl :ptr, :ptr, :gssize, :ptr, :ptr
g_io_channel_write_unichar proto __cdecl :ptr, :gunichar, :ptr
g_io_channel_seek_position proto __cdecl :ptr, :gint64, :GSeekType, :ptr
g_io_channel_new_file proto __cdecl :ptr, :ptr, :ptr
g_io_channel_error_quark proto __cdecl
g_io_channel_error_from_errno proto __cdecl :gint
g_io_channel_unix_new proto __cdecl :SINT
g_io_channel_unix_get_fd proto __cdecl :ptr

ifdef G_OS_WIN32

define G_WIN32_MSG_HANDLE 19981206

g_io_channel_win32_make_pollfd proto __cdecl :ptr, :GIOCondition, :ptr
g_io_channel_win32_poll proto __cdecl :ptr, :gint, :gint

if GLIB_SIZEOF_VOID_P EQ 8
g_io_channel_win32_new_messages proto __cdecl :gsize
else
g_io_channel_win32_new_messages proto __cdecl :guint
endif
g_io_channel_win32_new_fd proto __cdecl :gint
g_io_channel_win32_get_fd proto __cdecl :ptr
g_io_channel_win32_new_socket proto __cdecl :gint
g_io_channel_win32_new_stream_socket proto __cdecl :gint
g_io_channel_win32_set_debug proto __cdecl :ptr, :gboolean
endif

endif

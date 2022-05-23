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

G_IO_CHANNEL_ERROR equ <g_io_channel_error_quark>

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
funcs			ptr GIOFuncs ?
encoding		ptr gchar ?
read_cd			ptr GIConv ?
write_cd		ptr GIConv ?
line_term		ptr gchar ?
line_term_len		guint ?
buf_size		gsize ?
read_buf		ptr GString ?
encoded_read_buf	ptr GString ?
write_buf		ptr GString ?
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

CALLBACKC(GIOFunc, :ptr GIOChannel, :GIOCondition, :gpointer)

GIOFuncs		STRUC
io_read			proc :ptr GIOChannel, :ptr gchar, :gsize, :ptr gsize, :ptr GError
io_write		proc :ptr GIOChannel, :ptr gchar, :gsize, :ptr gsize, :ptr GError
io_seek			proc :ptr GIOChannel, :gint64, :GSeekType, :ptr GError
io_close		proc :ptr GIOChannel, :ptr GError
io_create_watch		proc :ptr GIOChannel, :GIOCondition
io_free			proc :ptr GIOChannel
io_set_flags		proc :ptr GIOChannel, :GIOFlags, :ptr GError
io_get_flags		proc :ptr GIOChannel
GIOFuncs		ENDS

;void
g_io_channel_init proto __cdecl \
	       channel: ptr GIOChannel

;GIOChannel
g_io_channel_ref proto __cdecl \
	       channel: ptr GIOChannel

;void
g_io_channel_unref proto __cdecl \
	       channel: ptr GIOChannel


g_io_channel_read proto __cdecl \
	       channel: ptr GIOChannel,
		   buf: ptr gchar,
		 count: gsize,
	    bytes_read: ptr gsize

g_io_channel_write proto __cdecl \
	       channel: ptr GIOChannel,
		   buf: ptr gchar,
		 count: gsize,
	 bytes_written: ptr gsize

g_io_channel_seek proto __cdecl \
	       channel: ptr GIOChannel,
		  offs: gint64,
		  type: GSeekType

;void
g_io_channel_close proto __cdecl \
	       channel: ptr GIOChannel


;GIOStatus
g_io_channel_shutdown proto __cdecl \
	       channel: ptr GIOChannel,
		 flush: gboolean,
		   err: ptr GError

;guint
g_io_add_watch_full proto __cdecl \
	       channel: ptr GIOChannel,
	      priority: gint,
	     condition: GIOCondition,
		  func: GIOFunc,
	     user_data: gpointer,
		notify: GDestroyNotify

;GSource
g_io_create_watch proto __cdecl \
	       channel: ptr GIOChannel,
	     condition: GIOCondition

;guint
g_io_add_watch proto __cdecl \
	       channel: ptr GIOChannel,
	     condition: GIOCondition,
		  func: GIOFunc,
	     user_data: gpointer


;void
g_io_channel_set_buffer_size proto __cdecl \
	       channel: ptr GIOChannel,
		  size: gsize

;gsize
g_io_channel_get_buffer_size proto __cdecl \
	       channel: ptr GIOChannel

;GIOCondition
g_io_channel_get_buffer_condition proto __cdecl \
	       channel: ptr GIOChannel

;GIOStatus
g_io_channel_set_flags proto __cdecl \
	       channel: ptr GIOChannel,
		 flags: GIOFlags,
		 error: ptr GError

;GIOFlags
g_io_channel_get_flags proto __cdecl \
	       channel: ptr GIOChannel

;void
g_io_channel_set_line_term proto __cdecl \
	       channel: ptr GIOChannel,
	     line_term: ptr gchar,
		length: gint

;const
g_io_channel_get_line_term proto __cdecl \
	       channel: ptr GIOChannel,
		length: ptr gint

;void
g_io_channel_set_buffered proto __cdecl \
	       channel: ptr GIOChannel,
	      buffered: gboolean

;gboolean
g_io_channel_get_buffered proto __cdecl \
	       channel: ptr GIOChannel

;GIOStatus
g_io_channel_set_encoding proto __cdecl \
	       channel: ptr GIOChannel,
	      encoding: ptr gchar,
		 error: ptr GError

;const
g_io_channel_get_encoding proto __cdecl \
	       channel: ptr GIOChannel

;void
g_io_channel_set_close_on_unref proto __cdecl \
	       channel: ptr GIOChannel,
	      do_close: gboolean

;gboolean
g_io_channel_get_close_on_unref proto __cdecl \
	       channel: ptr GIOChannel



;GIOStatus
g_io_channel_flush proto __cdecl \
	       channel: ptr GIOChannel,
		 error: ptr GError

;GIOStatus
g_io_channel_read_line proto __cdecl \
	       channel: ptr GIOChannel,
	    str_return: ptr gchar,
		length: ptr gsize,
	terminator_pos: ptr gsize,
		 error: ptr GError

;GIOStatus
g_io_channel_read_line_string proto __cdecl \
	       channel: ptr GIOChannel,
		buffer: ptr GString,
	terminator_pos: ptr gsize,
		 error: ptr GError

;GIOStatus
g_io_channel_read_to_end proto __cdecl \
	       channel: ptr GIOChannel,
	    str_return: ptr gchar,
		length: ptr gsize,
		 error: ptr GError

;GIOStatus
g_io_channel_read_chars proto __cdecl \
	       channel: ptr GIOChannel,
		   buf: ptr gchar,
		 count: gsize,
	    bytes_read: ptr gsize,
		 error: ptr GError

;GIOStatus
g_io_channel_read_unichar proto __cdecl \
	       channel: ptr GIOChannel,
	       thechar: ptr gunichar,
		 error: ptr GError

;GIOStatus
g_io_channel_write_chars proto __cdecl \
	       channel: ptr GIOChannel,
		   buf: ptr gchar,
		 count: gssize,
	 bytes_written: ptr gsize,
		 error: ptr GError

;GIOStatus
g_io_channel_write_unichar proto __cdecl \
	       channel: ptr GIOChannel,
	       thechar: gunichar,
		 error: ptr GError

;GIOStatus
g_io_channel_seek_position proto __cdecl \
	       channel: ptr GIOChannel,
		  offs: gint64,
		  type: GSeekType,
		 error: ptr GError

;GIOChannel*
g_io_channel_new_file proto __cdecl \
	      filename: ptr gchar,
		  mode: ptr gchar,
		 error: ptr GError


;GQuark
g_io_channel_error_quark proto __cdecl
;GIOChannelError
g_io_channel_error_from_errno proto __cdecl \
		    en: gint


;GIOChannel*
g_io_channel_unix_new proto __cdecl \
		    fd: SINT

;gint
g_io_channel_unix_get_fd proto __cdecl \
	       channel: ptr GIOChannel




;GLIB_VAR GSourceFuncs g_io_watch_funcs;

ifdef G_OS_WIN32

define G_WIN32_MSG_HANDLE 19981206

;void
g_io_channel_win32_make_pollfd proto __cdecl \
	       channel: ptr GIOChannel,
	     condition: GIOCondition,
		    fd: ptr GPollFD


;gint
g_io_channel_win32_poll proto __cdecl \
		   fds: ptr GPollFD,
		 n_fds: gint,
	      timeout_: gint



if GLIB_SIZEOF_VOID_P EQ 8
;GIOChannel
g_io_channel_win32_new_messages proto __cdecl \
		  hwnd: gsize

else
;GIOChannel
g_io_channel_win32_new_messages proto __cdecl \
		  hwnd: guint

endif

;GIOChannel*
g_io_channel_win32_new_fd proto __cdecl \
		    fd: gint



;gint
g_io_channel_win32_get_fd proto __cdecl \
	       channel: ptr GIOChannel


;GIOChannel
g_io_channel_win32_new_socket proto __cdecl \
		socket: gint


g_io_channel_win32_new_stream_socket proto __cdecl \
		socket: gint

;void
g_io_channel_win32_set_debug proto __cdecl \
	       channel: ptr GIOChannel,
		  flag: gboolean

endif

endif

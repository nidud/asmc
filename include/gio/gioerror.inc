ifndef __G_IO_ERROR_H__
define __G_IO_ERROR_H__

if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include glib.inc
include gio/gioenums.inc

G_IO_ERROR equ <g_io_error_quark>

;GQuark
g_io_error_quark proto __cdecl
;GIOErrorEnum
g_io_error_from_errno proto __cdecl \
                err_no: gint

ifdef G_OS_WIN32
;GIOErrorEnum
g_io_error_from_win32_error proto __cdecl \
            error_code: gint

endif

endif

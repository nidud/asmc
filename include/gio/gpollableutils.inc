ifndef __G_POLLABLE_UTILS_H__
define __G_POLLABLE_UTILS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gio.inc

g_pollable_source_new proto :ptr
g_pollable_source_new_full proto :gpointer, :ptr, :ptr
g_pollable_stream_read proto :ptr, :ptr, :gsize, :gboolean, :ptr, :ptr
g_pollable_stream_write proto :ptr, :ptr, :gsize, :gboolean, :ptr, :ptr
g_pollable_stream_write_all proto :ptr, :ptr, :gsize, :gboolean, :ptr, :ptr, :ptr

endif

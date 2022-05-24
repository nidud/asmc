ifndef __GDK_CLIPBOARD_H__
define __GDK_CLIPBOARD_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gio/gio.inc

define GDK_TYPE_CLIPBOARD            <gdk_clipboard_get_type ()>
GDK_CLIPBOARD macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_CLIPBOARD, GdkClipboard))>
  endm
GDK_IS_CLIPBOARD macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_CLIPBOARD))>
  endm

gdk_clipboard_get_type proto
gdk_clipboard_get_display proto :ptr
gdk_clipboard_get_formats proto :ptr
gdk_clipboard_is_local proto :ptr
gdk_clipboard_get_content proto :ptr
gdk_clipboard_store_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_clipboard_store_finish proto :ptr, :ptr, :ptr
gdk_clipboard_read_async proto :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_clipboard_read_finish proto :ptr, :ptr, :ptr, :ptr
gdk_clipboard_read_value_async proto :ptr, :GType, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_clipboard_read_value_finish proto :ptr, :ptr, :ptr
gdk_clipboard_read_texture_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
gdk_clipboard_read_texture_finish proto :ptr, :ptr, :ptr
gdk_clipboard_read_text_async proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
gdk_clipboard_read_text_finish proto :ptr, :ptr, :ptr
gdk_clipboard_set_content proto :ptr, :ptr
gdk_clipboard_set proto :ptr, :GType, :vararg
gdk_clipboard_set_valist proto :ptr, :GType, :va_list
gdk_clipboard_set_value proto :ptr, :ptr
gdk_clipboard_set_text proto :ptr, :ptr
gdk_clipboard_set_texture proto :ptr, :ptr

endif

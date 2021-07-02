ifndef __GTK_CLIPBOARD_H__
__GTK_CLIPBOARD_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkselection.inc

GTK_TYPE_CLIPBOARD equ <gtk_clipboard_get_type>
GTK_CLIPBOARD macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CLIPBOARD, GtkClipboard))>
	endm
GTK_IS_CLIPBOARD macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CLIPBOARD))>
	endm

CALLBACKC(GtkClipboardReceivedFunc, :ptr GtkClipboard, :ptr GtkSelectionData, :gpointer)
CALLBACKC(GtkClipboardTextReceivedFunc, :ptr GtkClipboard, :ptr gchar, :gpointer)
CALLBACKC(GtkClipboardRichTextReceivedFunc, :ptr GtkClipboard, :GdkAtom, :ptr guint8, :gsize, :gpointer)
CALLBACKC(GtkClipboardImageReceivedFunc, :ptr GtkClipboard, :ptr GdkPixbuf, :gpointer)
CALLBACKC(GtkClipboardURIReceivedFunc, :ptr GtkClipboard, :ptr ptr gchar, :gpointer)
CALLBACKC(GtkClipboardTargetsReceivedFunc, :ptr GtkClipboard, :ptr GdkAtom, :gint, :gpointer)
CALLBACKC(GtkClipboardGetFunc, :ptr GtkClipboard, :ptr GtkSelectionData, :guint, :gpointer)
CALLBACKC(GtkClipboardClearFunc, :ptr GtkClipboard, :gpointer)

;GType
gtk_clipboard_get_type proto __cdecl

;GtkClipboard
gtk_clipboard_get_for_display proto __cdecl \
	       display: ptr GdkDisplay,
	     selection: GdkAtom

;GtkClipboard
gtk_clipboard_get proto __cdecl \
	     selection: GdkAtom


;GtkClipboard
gtk_clipboard_get_default proto __cdecl \
	       display: ptr GdkDisplay


;GdkDisplay
gtk_clipboard_get_display proto __cdecl \
	     clipboard: ptr GtkClipboard



;gboolean
gtk_clipboard_set_with_data proto __cdecl \
	     clipboard: ptr GtkClipboard,
	       targets: ptr GtkTargetEntry,
	     n_targets: guint,
	      get_func: GtkClipboardGetFunc,
	    clear_func: GtkClipboardClearFunc,
	     user_data: gpointer

;gboolean
gtk_clipboard_set_with_owner proto __cdecl \
	     clipboard: ptr GtkClipboard,
	       targets: ptr GtkTargetEntry,
	     n_targets: guint,
	      get_func: GtkClipboardGetFunc,
	    clear_func: GtkClipboardClearFunc,
		 owner: ptr GObject

;GObject
gtk_clipboard_get_owner proto __cdecl \
	     clipboard: ptr GtkClipboard

;void
gtk_clipboard_clear proto __cdecl \
	     clipboard: ptr GtkClipboard

;void
gtk_clipboard_set_text proto __cdecl \
	     clipboard: ptr GtkClipboard,
		  text: ptr gchar,
		   len: gint

;void
gtk_clipboard_set_image proto __cdecl \
	     clipboard: ptr GtkClipboard,
		pixbuf: ptr GdkPixbuf


;void
gtk_clipboard_request_contents proto __cdecl \
	     clipboard: ptr GtkClipboard,
		target: GdkAtom,
	      callback: GtkClipboardReceivedFunc,
	     user_data: gpointer

;void
gtk_clipboard_request_text proto __cdecl \
	     clipboard: ptr GtkClipboard,
	      callback: GtkClipboardTextReceivedFunc,
	     user_data: gpointer

;void
gtk_clipboard_request_rich_text proto __cdecl \
	     clipboard: ptr GtkClipboard,
		buffer: ptr GtkTextBuffer,
	      callback: GtkClipboardRichTextReceivedFunc,
	     user_data: gpointer

;void
gtk_clipboard_request_image proto __cdecl \
	     clipboard: ptr GtkClipboard,
	      callback: GtkClipboardImageReceivedFunc,
	     user_data: gpointer

;void
gtk_clipboard_request_uris proto __cdecl \
	     clipboard: ptr GtkClipboard,
	      callback: GtkClipboardURIReceivedFunc,
	     user_data: gpointer

;void
gtk_clipboard_request_targets proto __cdecl \
	     clipboard: ptr GtkClipboard,
	      callback: GtkClipboardTargetsReceivedFunc,
	     user_data: gpointer


;GtkSelectionData
gtk_clipboard_wait_for_contents proto __cdecl \
	     clipboard: ptr GtkClipboard,
		target: GdkAtom

;gchar
gtk_clipboard_wait_for_text proto __cdecl \
	     clipboard: ptr GtkClipboard

;guint8
gtk_clipboard_wait_for_rich_text proto __cdecl \
	     clipboard: ptr GtkClipboard,
		buffer: ptr GtkTextBuffer,
		format: ptr GdkAtom,
		length: ptr gsize

;GdkPixbuf
gtk_clipboard_wait_for_image proto __cdecl \
	     clipboard: ptr GtkClipboard

;gchar
gtk_clipboard_wait_for_uris proto __cdecl \
	     clipboard: ptr GtkClipboard

;gboolean
gtk_clipboard_wait_for_targets proto __cdecl \
	     clipboard: ptr GtkClipboard,
	       targets: ptr GdkAtom,
	     n_targets: ptr gint


;gboolean
gtk_clipboard_wait_is_text_available proto __cdecl \
	     clipboard: ptr GtkClipboard

;gboolean
gtk_clipboard_wait_is_rich_text_available proto __cdecl \
	     clipboard: ptr GtkClipboard,
		buffer: ptr GtkTextBuffer

;gboolean
gtk_clipboard_wait_is_image_available proto __cdecl \
	     clipboard: ptr GtkClipboard

;gboolean
gtk_clipboard_wait_is_uris_available proto __cdecl \
	     clipboard: ptr GtkClipboard

;gboolean
gtk_clipboard_wait_is_target_available proto __cdecl \
	     clipboard: ptr GtkClipboard,
		target: GdkAtom



;void
gtk_clipboard_set_can_store proto __cdecl \
	     clipboard: ptr GtkClipboard,
	       targets: ptr GtkTargetEntry,
	     n_targets: gint


;void
gtk_clipboard_store proto __cdecl \
	     clipboard: ptr GtkClipboard


;void
_gtk_clipboard_handle_event proto __cdecl \
		 event: ptr GdkEventOwnerChange


;void
_gtk_clipboard_store_all proto __cdecl

endif

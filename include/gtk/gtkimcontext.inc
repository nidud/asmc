ifndef __GTK_IM_CONTEXT_H__
__GTK_IM_CONTEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

GTK_TYPE_IM_CONTEXT equ <gtk_im_context_get_type>
GTK_IM_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IM_CONTEXT, GtkIMContext))>
	endm
GTK_IM_CONTEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IM_CONTEXT, GtkIMContextClass))>
	endm
GTK_IS_IM_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IM_CONTEXT))>
	endm
GTK_IS_IM_CONTEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IM_CONTEXT))>
	endm
GTK_IM_CONTEXT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IM_CONTEXT, GtkIMContextClass))>
	endm


GtkIMContext		STRUC
parent_instance		GObject <>
GtkIMContext		ENDS

GtkIMContextClass	STRUC
parent_class		GObjectClass <>
preedit_start		proc :ptr GtkIMContext
preedit_end		proc :ptr GtkIMContext
preedit_changed		proc :ptr GtkIMContext
commit			proc :ptr GtkIMContext, :ptr gchar
retrieve_surrounding	proc :ptr GtkIMContext
delete_surrounding	proc :ptr GtkIMContext, :gboolean, :gint, :gint
set_client_window	proc :ptr GtkIMContext, :ptr GdkWindow
get_preedit_string	proc :ptr GtkIMContext, :ptr gchar, :ptr PangoAttrList, :ptr gint
filter_keypress		proc :ptr GtkIMContext, :ptr GdkEventKey
focus_in		proc :ptr GtkIMContext
focus_ou		proc :ptr GtkIMContext
reset			proc :ptr GtkIMContext
set_cursor_location	proc :ptr GtkIMContext, :ptr GdkRectangle
set_use_preedit		proc :ptr GtkIMContext, :gboolean
set_surrounding		proc :ptr GtkIMContext, :ptr gchar, :gint, :gint
get_surrounding		proc :ptr GtkIMContext, :ptr gchar, :ptr gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
GtkIMContextClass	ENDS

;GType
gtk_im_context_get_type proto __cdecl

;void
gtk_im_context_set_client_window proto __cdecl \
	       context: ptr GtkIMContext,
		window: ptr GdkWindow

;void
gtk_im_context_get_preedit_string proto __cdecl \
	       context: ptr GtkIMContext,
		  _str: ptr gchar,
		 attrs: ptr PangoAttrList,
	    cursor_pos: ptr gint

;gboolean
gtk_im_context_filter_keypress proto __cdecl \
	       context: ptr GtkIMContext,
		 event: ptr GdkEventKey

;void
gtk_im_context_focus_in proto __cdecl \
	       context: ptr GtkIMContext

;void
gtk_im_context_focus_out proto __cdecl \
	       context: ptr GtkIMContext

;void
gtk_im_context_reset proto __cdecl \
	       context: ptr GtkIMContext

;void
gtk_im_context_set_cursor_location proto __cdecl \
	       context: ptr GtkIMContext,
		  area: ptr GdkRectangle

;void
gtk_im_context_set_use_preedit proto __cdecl \
	       context: ptr GtkIMContext,
	   use_preedit: gboolean

;void
gtk_im_context_set_surrounding proto __cdecl \
	       context: ptr GtkIMContext,
		  text: ptr gchar,
		   len: gint,
	  cursor_index: gint

;gboolean
gtk_im_context_get_surrounding proto __cdecl \
	       context: ptr GtkIMContext,
		  text: ptr gchar,
	  cursor_index: ptr gint

;gboolean
gtk_im_context_delete_surrounding proto __cdecl \
	       context: ptr GtkIMContext,
	       _offset: gint,
	       n_chars: gint

endif

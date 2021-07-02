ifndef __GTK_INFO_BAR_H__
__GTK_INFO_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_INFO_BAR equ <gtk_info_bar_get_type>
GTK_INFO_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_INFO_BAR, GtkInfoBar))>
	endm
GTK_INFO_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_INFO_BAR, GtkInfoBarClass))>
	endm
GTK_IS_INFO_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_INFO_BAR))>
	endm
GTK_IS_INFO_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_INFO_BAR))>
	endm
GTK_INFO_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_INFO_BAR, GtkInfoBarClass))>
	endm


GtkInfoBar		STRUC
parent			GtkBox <>
priv			ptr_t ?
GtkInfoBar		ENDS

GtkInfoBarClass		STRUC
parent_class		GtkBoxClass <>
response		proc :ptr GtkInfoBar, :gint
close			proc :ptr GtkInfoBar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkInfoBarClass		ENDS

;GType
gtk_info_bar_get_type proto __cdecl
;GtkWidget
gtk_info_bar_new proto __cdecl

;GtkWidget
gtk_info_bar_new_with_buttons proto _CDecl \
     first_button_text: ptr gchar,
		      : vararg


;GtkWidget
gtk_info_bar_get_action_area proto __cdecl \
	      info_bar: ptr GtkInfoBar

;GtkWidget
gtk_info_bar_get_content_area proto __cdecl \
	      info_bar: ptr GtkInfoBar

;void
gtk_info_bar_add_action_widget proto __cdecl \
	      info_bar: ptr GtkInfoBar,
		 child: ptr GtkWidget,
	   response_id: gint

;GtkWidget
gtk_info_bar_add_button proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	   button_text: ptr gchar,
	   response_id: gint

;void
gtk_info_bar_add_buttons proto _CDecl \
	      info_bar: ptr GtkInfoBar,
     first_button_text: ptr gchar,
		      : vararg

;void
gtk_info_bar_set_response_sensitive proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	   response_id: gint,
	       setting: gboolean

;void
gtk_info_bar_set_default_response proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	   response_id: gint


;void
gtk_info_bar_response proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	   response_id: gint


;void
gtk_info_bar_set_message_type proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	  message_type: GtkMessageType

;GtkMessageType
gtk_info_bar_get_message_type proto __cdecl \
	      info_bar: ptr GtkInfoBar


;void
gtk_info_bar_set_show_close_button proto __cdecl \
	      info_bar: ptr GtkInfoBar,
	       setting: gboolean

;gboolean
gtk_info_bar_get_show_close_button proto __cdecl \
	      info_bar: ptr GtkInfoBar

G_END_DECLS

endif

ifndef __GTK_LINK_BUTTON_H__
__GTK_LINK_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

G_BEGIN_DECLS

GTK_TYPE_LINK_BUTTON equ <gtk_link_button_get_type>
GTK_LINK_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LINK_BUTTON, GtkLinkButton))>
	endm
GTK_IS_LINK_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LINK_BUTTON))>
	endm
GTK_LINK_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LINK_BUTTON, GtkLinkButtonClass))>
	endm
GTK_IS_LINK_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LINK_BUTTON))>
	endm
GTK_LINK_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LINK_BUTTON, GtkLinkButtonClass))>
	endm

GtkLinkButton		STRUC
parent_instance		GtkButton <>
priv			ptr_t ?
GtkLinkButton		ENDS

GtkLinkButtonClass	STRUC
parent_class		GtkButtonClass <>
activate_link		proc :ptr GtkLinkButton
_gtk_padding1		proc
_gtk_padding2		proc
_gtk_padding3		proc
_gtk_padding4		proc
GtkLinkButtonClass	ENDS

;GType
gtk_link_button_get_type proto __cdecl

;GtkWidget
gtk_link_button_new proto __cdecl \
		   uri: ptr gchar

;GtkWidget
gtk_link_button_new_with_label proto __cdecl \
		   uri: ptr gchar,
		_label: ptr gchar


;const
gtk_link_button_get_uri proto __cdecl \
	   link_button: ptr GtkLinkButton

;void
gtk_link_button_set_uri proto __cdecl \
	   link_button: ptr GtkLinkButton,
		   uri: ptr gchar


;gboolean
gtk_link_button_get_visited proto __cdecl \
	   link_button: ptr GtkLinkButton

;void
gtk_link_button_set_visited proto __cdecl \
	   link_button: ptr GtkLinkButton,
	       visited: gboolean


G_END_DECLS

endif

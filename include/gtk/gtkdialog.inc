ifndef __GTK_DIALOG_H__
__GTK_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

.enum GtkDialogFlags {
  GTK_DIALOG_MODAL		 = 1 shl 0,
  GTK_DIALOG_DESTROY_WITH_PARENT = 1 shl 1,
  GTK_DIALOG_USE_HEADER_BAR	 = 1 shl 2
}

.enum GtkResponseType {
  GTK_RESPONSE_NONE	    = -1,
  GTK_RESPONSE_REJECT	    = -2,
  GTK_RESPONSE_ACCEPT	    = -3,
  GTK_RESPONSE_DELETE_EVENT = -4,
  GTK_RESPONSE_OK	    = -5,
  GTK_RESPONSE_CANCEL	    = -6,
  GTK_RESPONSE_CLOSE	    = -7,
  GTK_RESPONSE_YES	    = -8,
  GTK_RESPONSE_NO	    = -9,
  GTK_RESPONSE_APPLY	    = -10,
  GTK_RESPONSE_HELP	    = -11
}


GTK_TYPE_DIALOG equ <gtk_dialog_get_type>
GTK_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_DIALOG, GtkDialog))>
	endm
GTK_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_DIALOG, GtkDialogClass))>
	endm
GTK_IS_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_DIALOG))>
	endm
GTK_IS_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_DIALOG))>
	endm
GTK_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_DIALOG, GtkDialogClass))>
	endm

GtkDialog		STRUC
window			GtkWindow <>
priv			ptr_t ?
GtkDialog		ENDS

GtkDialogClass		STRUC
parent_class		GtkWindowClass <>
response		proc :ptr GtkDialog, :gint
close			proc :ptr GtkDialog
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkDialogClass		ENDS

;GType
gtk_dialog_get_type proto __cdecl
;GtkWidget*
gtk_dialog_new proto __cdecl

;GtkWidget*
gtk_dialog_new_with_buttons proto _CDecl \
		 title: ptr gchar,
		parent: ptr GtkWindow,
		 flags: GtkDialogFlags,
     first_button_text: ptr gchar,
		      : vararg

;void
gtk_dialog_add_action_widget proto __cdecl \
		dialog: ptr GtkDialog,
		 child: ptr GtkWidget,
	   response_id: gint

;GtkWidget*
gtk_dialog_add_button proto __cdecl \
		dialog: ptr GtkDialog,
	   button_text: ptr gchar,
	   response_id: gint

;void
gtk_dialog_add_buttons proto _CDecl \
		dialog: ptr GtkDialog,
     first_button_text: ptr gchar,
		      : vararg

;void
gtk_dialog_set_response_sensitive proto __cdecl \
		dialog: ptr GtkDialog,
	   response_id: gint,
	       setting: gboolean

;void
gtk_dialog_set_default_response proto __cdecl \
		dialog: ptr GtkDialog,
	   response_id: gint

;GtkWidget*
gtk_dialog_get_widget_for_response proto __cdecl \
		dialog: ptr GtkDialog,
	   response_id: gint

;gint
gtk_dialog_get_response_for_widget proto __cdecl \
		dialog: ptr GtkDialog,
		widget: ptr GtkWidget


;gboolean
gtk_alternative_dialog_button_order proto __cdecl \
		screen: ptr GdkScreen

;void
gtk_dialog_set_alternative_button_order proto _CDecl \
		dialog: ptr GtkDialog,
     first_response_id: gint,
		      : vararg

;void
gtk_dialog_set_alternative_button_order_from_array proto __cdecl \
		dialog: ptr GtkDialog,
	      n_params: gint,
	     new_order: ptr gint


;void
gtk_dialog_response proto __cdecl \
		dialog: ptr GtkDialog,
	   response_id: gint


;gint
gtk_dialog_run proto __cdecl \
		dialog: ptr GtkDialog


;GtkWidget
gtk_dialog_get_action_area proto __cdecl \
		dialog: ptr GtkDialog

;GtkWidget
gtk_dialog_get_content_area proto __cdecl \
		dialog: ptr GtkDialog

;GtkWidget
gtk_dialog_get_header_bar proto __cdecl \
		dialog: ptr GtkDialog


G_END_DECLS

endif

ifndef __GTK_MESSAGE_DIALOG_H__
__GTK_MESSAGE_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_MESSAGE_DIALOG equ <gtk_message_dialog_get_type>
GTK_MESSAGE_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialog))>
	endm
GTK_MESSAGE_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialogClass))>
	endm
GTK_IS_MESSAGE_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MESSAGE_DIALOG))>
	endm
GTK_IS_MESSAGE_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MESSAGE_DIALOG))>
	endm
GTK_MESSAGE_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialogClass))>
	endm

GtkMessageDialog	STRUC
parent_instance		GtkDialog <>
priv			ptr_t ?
GtkMessageDialog	ENDS

GtkMessageDialogClass	STRUC
parent_class		GtkDialogClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMessageDialogClass	ENDS

.enum GtkButtonsType {
  GTK_BUTTONS_NONE,
  GTK_BUTTONS_OK,
  GTK_BUTTONS_CLOSE,
  GTK_BUTTONS_CANCEL,
  GTK_BUTTONS_YES_NO,
  GTK_BUTTONS_OK_CANCEL
}

;GType
gtk_message_dialog_get_type proto __cdecl

;GtkWidget*
gtk_message_dialog_new proto _CDecl \
		parent: ptr GtkWindow,
		 flags: GtkDialogFlags,
		  type: GtkMessageType,
	       buttons: GtkButtonsType,
	message_format: ptr gchar,


;GtkWidget*
gtk_message_dialog_new_with_markup proto _CDecl \
		parent: ptr GtkWindow,
		 flags: GtkDialogFlags,
		  type: GtkMessageType,
	       buttons: GtkButtonsType,
	message_format: ptr gchar,


;void
gtk_message_dialog_set_image proto __cdecl \
		dialog: ptr GtkMessageDialog,
		 image: ptr GtkWidget


;GtkWidget
gtk_message_dialog_get_image proto __cdecl \
		dialog: ptr GtkMessageDialog


;void
gtk_message_dialog_set_markup proto __cdecl \
	message_dialog: ptr GtkMessageDialog,
		  _str: ptr gchar


;void
gtk_message_dialog_format_secondary_text proto _CDecl \
	message_dialog: ptr GtkMessageDialog,
	message_format: ptr gchar,


;void
gtk_message_dialog_format_secondary_markup proto _CDecl \
	message_dialog: ptr GtkMessageDialog,
	message_format: ptr gchar,


;GtkWidget
gtk_message_dialog_get_message_area proto __cdecl \
	message_dialog: ptr GtkMessageDialog


G_END_DECLS

endif

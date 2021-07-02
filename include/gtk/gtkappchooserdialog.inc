ifndef __GTK_APP_CHOOSER_DIALOG_H__
__GTK_APP_CHOOSER_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gio/gio.inc

G_BEGIN_DECLS

GTK_TYPE_APP_CHOOSER_DIALOG equ <gtk_app_chooser_dialog_get_type>
GTK_APP_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_DIALOG, GtkAppChooserDialog))>
	endm
GTK_APP_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_APP_CHOOSER_DIALOG, GtkAppChooserDialogClass))>
	endm
GTK_IS_APP_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_DIALOG))>
	endm
GTK_IS_APP_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_APP_CHOOSER_DIALOG))>
	endm
GTK_APP_CHOOSER_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_APP_CHOOSER_DIALOG, GtkAppChooserDialogClass))>
	endm

GtkAppChooserDialog	STRUC
parent			GtkDialog <>
priv			ptr_t ?
GtkAppChooserDialog	ENDS

GtkAppChooserDialogClass STRUC
parent_class		GtkDialogClass <>
padding			gpointer 16 dup(?)
GtkAppChooserDialogClass ENDS

;GType
gtk_app_chooser_dialog_get_type proto __cdecl

;GtkWidget
gtk_app_chooser_dialog_new proto __cdecl \
		parent: ptr GtkWindow,
		 flags: GtkDialogFlags,
		  file: ptr GFile

;GtkWidget
gtk_app_chooser_dialog_new_for_content_type proto __cdecl \
		parent: ptr GtkWindow,
		 flags: GtkDialogFlags,
	  content_type: ptr gchar


;GtkWidget
gtk_app_chooser_dialog_get_widget proto __cdecl \
		  self: ptr GtkAppChooserDialog

;void
gtk_app_chooser_dialog_set_heading proto __cdecl \
		  self: ptr GtkAppChooserDialog,
	       heading: ptr gchar

;const
gtk_app_chooser_dialog_get_heading proto __cdecl \
		  self: ptr GtkAppChooserDialog

G_END_DECLS

endif

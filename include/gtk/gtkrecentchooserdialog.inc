ifndef __GTK_RECENT_CHOOSER_DIALOG_H__
__GTK_RECENT_CHOOSER_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gtk/gtkrecentchooser.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_CHOOSER_DIALOG equ <gtk_recent_chooser_dialog_get_type>
GTK_RECENT_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_CHOOSER_DIALOG, GtkRecentChooserDialog))>
	endm
GTK_IS_RECENT_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_CHOOSER_DIALOG))>
	endm
GTK_RECENT_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RECENT_CHOOSER_DIALOG, GtkRecentChooserDialogClass))>
	endm
GTK_IS_RECENT_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RECENT_CHOOSER_DIALOG))>
	endm
GTK_RECENT_CHOOSER_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RECENT_CHOOSER_DIALOG, GtkRecentChooserDialogClass))>
	endm

GtkRecentChooserDialog	STRUC
parent_instance		GtkDialog <>
priv			ptr_t ?
GtkRecentChooserDialog	ENDS

GtkRecentChooserDialogClass STRUC
parent_class		GtkDialogClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRecentChooserDialogClass ENDS


;GType
gtk_recent_chooser_dialog_get_type proto __cdecl

;GtkWidget
gtk_recent_chooser_dialog_new proto _CDecl \
		 title: ptr gchar,
		parent: ptr GtkWindow,
     first_button_text: ptr gchar,
		      : vararg

;GtkWidget
gtk_recent_chooser_dialog_new_for_manager proto _CDecl \
		 title: ptr gchar,
		parent: ptr GtkWindow,
	       manager: ptr GtkRecentManager,
     first_button_text: ptr gchar,
		      : vararg

G_END_DECLS

endif

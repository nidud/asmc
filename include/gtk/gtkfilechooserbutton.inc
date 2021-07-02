ifndef __GTK_FILE_CHOOSER_BUTTON_H__
__GTK_FILE_CHOOSER_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc
include gtk/gtkfilechooser.inc

G_BEGIN_DECLS

GTK_TYPE_FILE_CHOOSER_BUTTON equ <gtk_file_chooser_button_get_type>
GTK_FILE_CHOOSER_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER_BUTTON, GtkFileChooserButton))>
	endm
GTK_FILE_CHOOSER_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FILE_CHOOSER_BUTTON, GtkFileChooserButtonClass))>
	endm
GTK_IS_FILE_CHOOSER_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER_BUTTON))>
	endm
GTK_IS_FILE_CHOOSER_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FILE_CHOOSER_BUTTON))>
	endm
GTK_FILE_CHOOSER_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FILE_CHOOSER_BUTTON, GtkFileChooserButtonClass))>
	endm

GtkFileChooserButton	STRUC
parent			GtkBox <>
priv			ptr_t ?
GtkFileChooserButton	ENDS

GtkFileChooserButtonClass STRUC
parent_class		GtkBoxClass <>
file_set		proc :ptr GtkFileChooserButton
__gtk_reserved1		proc
__gtk_reserved2		proc
__gtk_reserved3		proc
__gtk_reserved4		proc
GtkFileChooserButtonClass ENDS


;GType
gtk_file_chooser_button_get_type proto __cdecl
;GtkWidget
gtk_file_chooser_button_new proto __cdecl \
		 title: ptr gchar,
		action: GtkFileChooserAction

;GtkWidget
gtk_file_chooser_button_new_with_dialog proto __cdecl \
		dialog: ptr GtkWidget

;const
gtk_file_chooser_button_get_title proto __cdecl \
		button: ptr GtkFileChooserButton

;void
gtk_file_chooser_button_set_title proto __cdecl \
		button: ptr GtkFileChooserButton,
		 title: ptr gchar

;gint
gtk_file_chooser_button_get_width_chars proto __cdecl \
		button: ptr GtkFileChooserButton

;void
gtk_file_chooser_button_set_width_chars proto __cdecl \
		button: ptr GtkFileChooserButton,
	       n_chars: gint

;gboolean
gtk_file_chooser_button_get_focus_on_click proto __cdecl \
		button: ptr GtkFileChooserButton

;void
gtk_file_chooser_button_set_focus_on_click proto __cdecl \
		button: ptr GtkFileChooserButton,
	focus_on_click: gboolean


G_END_DECLS

endif

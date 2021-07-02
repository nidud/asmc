ifndef __GTK_FONT_CHOOSER_DIALOG_H__
__GTK_FONT_CHOOSER_DIALOG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc

G_BEGIN_DECLS

GTK_TYPE_FONT_CHOOSER_DIALOG equ <gtk_font_chooser_dialog_get_type>
GTK_FONT_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_CHOOSER_DIALOG, GtkFontChooserDialog))>
	endm
GTK_FONT_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FONT_CHOOSER_DIALOG, GtkFontChooserDialogClass))>
	endm
GTK_IS_FONT_CHOOSER_DIALOG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_CHOOSER_DIALOG))>
	endm
GTK_IS_FONT_CHOOSER_DIALOG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FONT_CHOOSER_DIALOG))>
	endm
GTK_FONT_CHOOSER_DIALOG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FONT_CHOOSER_DIALOG, GtkFontChooserDialogClass))>
	endm

GtkFontChooserDialog	STRUC
parent_instance		GtkDialog <>
priv			ptr_t ?
GtkFontChooserDialog	ENDS

GtkFontChooserDialogClass STRUC
parent_class		GtkDialogClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkFontChooserDialogClass ENDS

;GType
gtk_font_chooser_dialog_get_type proto __cdecl
;GtkWidget*
gtk_font_chooser_dialog_new proto __cdecl \
		 title: ptr gchar,
		parent: ptr GtkWindow

G_END_DECLS

endif

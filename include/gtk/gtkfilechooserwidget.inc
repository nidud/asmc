ifndef __GTK_FILE_CHOOSER_WIDGET_H__
__GTK_FILE_CHOOSER_WIDGET_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilechooser.inc
include gtk/gtkbox.inc

G_BEGIN_DECLS

GTK_TYPE_FILE_CHOOSER_WIDGET equ <gtk_file_chooser_widget_get_type>
GTK_FILE_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_CHOOSER_WIDGET, GtkFileChooserWidget))>
	endm
GTK_FILE_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FILE_CHOOSER_WIDGET, GtkFileChooserWidgetClass))>
	endm
GTK_IS_FILE_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_CHOOSER_WIDGET))>
	endm
GTK_IS_FILE_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FILE_CHOOSER_WIDGET))>
	endm
GTK_FILE_CHOOSER_WIDGET_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FILE_CHOOSER_WIDGET, GtkFileChooserWidgetClass))>
	endm

GtkFileChooserWidget	STRUC
parent_instance		GtkBox <>
priv			ptr_t ?
GtkFileChooserWidget	ENDS

GtkFileChooserWidgetClass STRUC
parent_class		GtkBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkFileChooserWidgetClass ENDS

;GType
gtk_file_chooser_widget_get_type proto __cdecl
;GtkWidget
gtk_file_chooser_widget_new proto __cdecl \
		action: GtkFileChooserAction

G_END_DECLS

endif

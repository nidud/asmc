ifndef __GTK_FONT_CHOOSER_WIDGET_H__
__GTK_FONT_CHOOSER_WIDGET_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc

G_BEGIN_DECLS

GTK_TYPE_FONT_CHOOSER_WIDGET equ <gtk_font_chooser_widget_get_type>
GTK_FONT_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_CHOOSER_WIDGET, GtkFontChooserWidget))>
	endm
GTK_FONT_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FONT_CHOOSER_WIDGET, GtkFontChooserWidgetClass))>
	endm
GTK_IS_FONT_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_CHOOSER_WIDGET))>
	endm
GTK_IS_FONT_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FONT_CHOOSER_WIDGET))>
	endm
GTK_FONT_CHOOSER_WIDGET_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FONT_CHOOSER_WIDGET, GtkFontChooserWidgetClass))>
	endm

GtkFontChooserWidget	STRUC
parent_instance		GtkBox <>
priv			ptr_t ?
GtkFontChooserWidget	ENDS

GtkFontChooserWidgetClass STRUC
parent_class		GtkBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkFontChooserWidgetClass ENDS

;GType
gtk_font_chooser_widget_get_type proto __cdecl

;GtkWidget*
gtk_font_chooser_widget_new proto __cdecl

G_END_DECLS

endif

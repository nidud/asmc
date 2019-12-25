ifndef __GTK_RECENT_CHOOSER_WIDGET_H__
__GTK_RECENT_CHOOSER_WIDGET_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkrecentchooser.inc
include gtk/gtkbox.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_CHOOSER_WIDGET equ <gtk_recent_chooser_widget_get_type>
GTK_RECENT_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_CHOOSER_WIDGET, GtkRecentChooserWidget))>
	endm
GTK_IS_RECENT_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_CHOOSER_WIDGET))>
	endm
GTK_RECENT_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RECENT_CHOOSER_WIDGET, GtkRecentChooserWidgetClass))>
	endm
GTK_IS_RECENT_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RECENT_CHOOSER_WIDGET))>
	endm
GTK_RECENT_CHOOSER_WIDGET_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RECENT_CHOOSER_WIDGET, GtkRecentChooserWidgetClass))>
	endm

GtkRecentChooserWidget	STRUC
parent_instance		GtkBox <>
priv			ptr_t ?
GtkRecentChooserWidget	ENDS

GtkRecentChooserWidgetClass STRUC
parent_class		GtkBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkRecentChooserWidgetClass ENDS

;GType
gtk_recent_chooser_widget_get_type proto __cdecl
;GtkWidget
gtk_recent_chooser_widget_new proto __cdecl
;GtkWidget
gtk_recent_chooser_widget_new_for_manager proto __cdecl \
	       manager: ptr GtkRecentManager


G_END_DECLS

endif

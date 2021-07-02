ifndef __GTK_APP_CHOOSER_WIDGET_H__
__GTK_APP_CHOOSER_WIDGET_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc
include gtk/gtkmenu.inc
include gio/gio.inc

G_BEGIN_DECLS

GTK_TYPE_APP_CHOOSER_WIDGET equ <gtk_app_chooser_widget_get_type>
GTK_APP_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_WIDGET, GtkAppChooserWidget))>
	endm
GTK_APP_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_APP_CHOOSER_WIDGET, GtkAppChooserWidgetClass))>
	endm
GTK_IS_APP_CHOOSER_WIDGET macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_WIDGET))>
	endm
GTK_IS_APP_CHOOSER_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_APP_CHOOSER_WIDGET))>
	endm
GTK_APP_CHOOSER_WIDGET_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_APP_CHOOSER_WIDGET, GtkAppChooserWidgetClass))>
	endm

GtkAppChooserWidget	STRUC
parent			GtkBox <>
priv			ptr_t ?
GtkAppChooserWidget	ENDS

GtkAppChooserWidgetClass STRUC
parent_class		GtkBoxClass <>
application_selected	proc :ptr GtkAppChooserWidget, :ptr GAppInfo
application_activated	proc :ptr GtkAppChooserWidget, :ptr GAppInfo
populate_popup		proc :ptr GtkAppChooserWidget, :ptr GtkMenu, :ptr GAppInfo
padding			gpointer 16 dup(?)
GtkAppChooserWidgetClass ENDS

;GType
gtk_app_chooser_widget_get_type proto __cdecl

;GtkWidget
gtk_app_chooser_widget_new proto __cdecl \
	  content_type: ptr gchar


;void
gtk_app_chooser_widget_set_show_default proto __cdecl \
		  self: ptr GtkAppChooserWidget,
	       setting: gboolean

;gboolean
gtk_app_chooser_widget_get_show_default proto __cdecl \
		  self: ptr GtkAppChooserWidget


;void
gtk_app_chooser_widget_set_show_recommended proto __cdecl \
		  self: ptr GtkAppChooserWidget,
	       setting: gboolean

;gboolean
gtk_app_chooser_widget_get_show_recommended proto __cdecl \
		  self: ptr GtkAppChooserWidget


;void
gtk_app_chooser_widget_set_show_fallback proto __cdecl \
		  self: ptr GtkAppChooserWidget,
	       setting: gboolean

;gboolean
gtk_app_chooser_widget_get_show_fallback proto __cdecl \
		  self: ptr GtkAppChooserWidget


;void
gtk_app_chooser_widget_set_show_other proto __cdecl \
		  self: ptr GtkAppChooserWidget,
	       setting: gboolean

;gboolean
gtk_app_chooser_widget_get_show_other proto __cdecl \
		  self: ptr GtkAppChooserWidget


;void
gtk_app_chooser_widget_set_show_all proto __cdecl \
		  self: ptr GtkAppChooserWidget,
	       setting: gboolean

;gboolean
gtk_app_chooser_widget_get_show_all proto __cdecl \
		  self: ptr GtkAppChooserWidget


;void
gtk_app_chooser_widget_set_default_text proto __cdecl \
		  self: ptr GtkAppChooserWidget,
		  text: ptr gchar

;const
gtk_app_chooser_widget_get_default_text proto __cdecl \
		  self: ptr GtkAppChooserWidget

G_END_DECLS

endif

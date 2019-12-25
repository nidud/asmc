ifndef __GTK_APP_CHOOSER_BUTTON_H__
__GTK_APP_CHOOSER_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcombobox.inc
include gio/gio.inc

G_BEGIN_DECLS

GTK_TYPE_APP_CHOOSER_BUTTON equ <gtk_app_chooser_button_get_type>
GTK_APP_CHOOSER_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER_BUTTON, GtkAppChooserButton))>
	endm
GTK_APP_CHOOSER_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_APP_CHOOSER_BUTTON, GtkAppChooserButtonClass))>
	endm
GTK_IS_APP_CHOOSER_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER_BUTTON))>
	endm
GTK_IS_APP_CHOOSER_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_APP_CHOOSER_BUTTON))>
	endm
GTK_APP_CHOOSER_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_APP_CHOOSER_BUTTON, GtkAppChooserButtonClass))>
	endm

GtkAppChooserButton	STRUC
parent			GtkComboBox <>
priv			ptr_t ?
GtkAppChooserButton	ENDS

GtkAppChooserButtonClass STRUC
parent_class		GtkComboBoxClass <>
custom_item_activated	proc :ptr GtkAppChooserButton, :ptr
padding			gpointer 16 dup(?)
GtkAppChooserButtonClass ENDS

;GType
gtk_app_chooser_button_get_type proto __cdecl

;GtkWidget
gtk_app_chooser_button_new proto __cdecl \
	  content_type: ptr gchar


;void
gtk_app_chooser_button_append_separator proto __cdecl \
		  self: ptr GtkAppChooserButton

;void
gtk_app_chooser_button_append_custom_item proto __cdecl \
		  self: ptr GtkAppChooserButton,
		  name: ptr gchar,
		_label: ptr gchar,
		  icon: ptr GIcon

;void
gtk_app_chooser_button_set_active_custom_item proto __cdecl \
		  self: ptr GtkAppChooserButton,
		  name: ptr gchar


;void
gtk_app_chooser_button_set_show_dialog_item proto __cdecl \
		  self: ptr GtkAppChooserButton,
	       setting: gboolean

;gboolean
gtk_app_chooser_button_get_show_dialog_item proto __cdecl \
		  self: ptr GtkAppChooserButton

;void
gtk_app_chooser_button_set_heading proto __cdecl \
		  self: ptr GtkAppChooserButton,
	       heading: ptr gchar

;const
gtk_app_chooser_button_get_heading proto __cdecl \
		  self: ptr GtkAppChooserButton

;void
gtk_app_chooser_button_set_show_default_item proto __cdecl \
		  self: ptr GtkAppChooserButton,
	       setting: gboolean

;gboolean
gtk_app_chooser_button_get_show_default_item proto __cdecl \
		  self: ptr GtkAppChooserButton

G_END_DECLS

endif

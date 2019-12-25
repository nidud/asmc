ifndef __GTK_APP_CHOOSER_H__
__GTK_APP_CHOOSER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gio/gio.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_APP_CHOOSER equ <gtk_app_chooser_get_type>
GTK_APP_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_APP_CHOOSER, GtkAppChooser))>
	endm
GTK_IS_APP_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_APP_CHOOSER))>
	endm

;GType
gtk_app_chooser_get_type proto __cdecl

;GAppInfo
gtk_app_chooser_get_app_info proto __cdecl \
		  self: ptr GtkAppChooser

;gchar
gtk_app_chooser_get_content_type proto __cdecl \
		  self: ptr GtkAppChooser

;void
gtk_app_chooser_refresh proto __cdecl \
		  self: ptr GtkAppChooser


G_END_DECLS

endif


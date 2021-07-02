ifndef __GTK_APPLICATION_WINDOW_H__
__GTK_APPLICATION_WINDOW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

GTK_TYPE_APPLICATION_WINDOW equ <gtk_application_window_get_type>
GTK_APPLICATION_WINDOW macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindow))>
	endm
GTK_APPLICATION_WINDOW_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindowClass))>
	endm
GTK_IS_APPLICATION_WINDOW macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), GTK_TYPE_APPLICATION_WINDOW))>
	endm
GTK_IS_APPLICATION_WINDOW_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), GTK_TYPE_APPLICATION_WINDOW))>
	endm
GTK_APPLICATION_WINDOW_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), GTK_TYPE_APPLICATION_WINDOW, GtkApplicationWindowClass))>
	endm

GtkApplicationWindow	STRUC
parent_instance		GtkWindow <>
priv			ptr_t ?
GtkApplicationWindow	ENDS

GtkApplicationWindowClass STRUC
parent_class		GtkWindowClass <>
padding			gpointer 14 dup(?)
GtkApplicationWindowClass ENDS

;GType
gtk_application_window_get_type proto __cdecl
;GtkWidget
gtk_application_window_new proto __cdecl \
	   application: ptr GtkApplication

;void
gtk_application_window_set_show_menubar proto __cdecl \
		window: ptr GtkApplicationWindow,
	  show_menubar: gboolean

;gboolean
gtk_application_window_get_show_menubar proto __cdecl \
		window: ptr GtkApplicationWindow

;guint
gtk_application_window_get_id proto __cdecl \
		window: ptr GtkApplicationWindow

G_END_DECLS

endif

ifndef __GTK_COLOR_BUTTON_H__
__GTK_COLOR_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

G_BEGIN_DECLS

GTK_TYPE_COLOR_BUTTON equ <gtk_color_button_get_type>
GTK_COLOR_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COLOR_BUTTON, GtkColorButton))>
	endm
GTK_COLOR_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_COLOR_BUTTON, GtkColorButtonClass))>
	endm
GTK_IS_COLOR_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COLOR_BUTTON))>
	endm
GTK_IS_COLOR_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_COLOR_BUTTON))>
	endm
GTK_COLOR_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_COLOR_BUTTON, GtkColorButtonClass))>
	endm

GtkColorButton		STRUC
button			GtkButton <>
priv			ptr_t ?
GtkColorButton		ENDS

GtkColorButtonClass	STRUC
parent_class		GtkButtonClass <>
 color_set		proc :ptr GtkColorButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkColorButtonClass	ENDS


;GType
gtk_color_button_get_type proto __cdecl
;GtkWidget
gtk_color_button_new proto __cdecl
;GtkWidget
gtk_color_button_new_with_rgba proto __cdecl \
		  rgba: ptr GdkRGBA

;void
gtk_color_button_set_title proto __cdecl \
		button: ptr GtkColorButton,
		 title: ptr gchar

;const
gtk_color_button_get_title proto __cdecl \
		button: ptr GtkColorButton


;GtkWidget
gtk_color_button_new_with_color proto __cdecl \
		 color: ptr GdkColor

;void
gtk_color_button_set_color proto __cdecl \
		button: ptr GtkColorButton,
		 color: ptr GdkColor

;void
gtk_color_button_get_color proto __cdecl \
		button: ptr GtkColorButton,
		 color: ptr GdkColor

;void
gtk_color_button_set_alpha proto __cdecl \
		button: ptr GtkColorButton,
		 alpha: guint16

;guint16
gtk_color_button_get_alpha proto __cdecl \
		button: ptr GtkColorButton

;void
gtk_color_button_set_use_alpha proto __cdecl \
		button: ptr GtkColorButton,
	     use_alpha: gboolean

;gboolean
gtk_color_button_get_use_alpha proto __cdecl \
		button: ptr GtkColorButton

;void
gtk_color_button_set_rgba proto __cdecl \
		button: ptr GtkColorButton,
		  rgba: ptr GdkRGBA

;void
gtk_color_button_get_rgba proto __cdecl \
		button: ptr GtkColorButton,
		  rgba: ptr GdkRGBA

G_END_DECLS

endif

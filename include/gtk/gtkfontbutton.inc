ifndef __GTK_FONT_BUTTON_H__
__GTK_FONT_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

G_BEGIN_DECLS

GTK_TYPE_FONT_BUTTON equ <gtk_font_button_get_type>
GTK_FONT_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_BUTTON, GtkFontButton))>
	endm
GTK_FONT_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FONT_BUTTON, GtkFontButtonClass))>
	endm
GTK_IS_FONT_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_BUTTON))>
	endm
GTK_IS_FONT_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FONT_BUTTON))>
	endm
GTK_FONT_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FONT_BUTTON, GtkFontButtonClass))>
	endm

GtkFontButton		STRUC
button			GtkButton <>
priv			ptr_t ?
GtkFontButton		ENDS

GtkFontButtonClass	STRUC
parent_class		GtkButtonClass <>
font_set		proc :ptr GtkFontButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkFontButtonClass	ENDS


;GType
gtk_font_button_get_type proto __cdecl
;GtkWidget
gtk_font_button_new proto __cdecl
;GtkWidget
gtk_font_button_new_with_font proto __cdecl \
	      fontname: ptr gchar

;const
gtk_font_button_get_title proto __cdecl \
	   font_button: ptr GtkFontButton

;void
gtk_font_button_set_title proto __cdecl \
	   font_button: ptr GtkFontButton,
		 title: ptr gchar

;gboolean
gtk_font_button_get_use_font proto __cdecl \
	   font_button: ptr GtkFontButton

;void
gtk_font_button_set_use_font proto __cdecl \
	   font_button: ptr GtkFontButton,
	      use_font: gboolean

;gboolean
gtk_font_button_get_use_size proto __cdecl \
	   font_button: ptr GtkFontButton

;void
gtk_font_button_set_use_size proto __cdecl \
	   font_button: ptr GtkFontButton,
	      use_size: gboolean

;const
gtk_font_button_get_font_name proto __cdecl \
	   font_button: ptr GtkFontButton

;gboolean
gtk_font_button_set_font_name proto __cdecl \
	   font_button: ptr GtkFontButton,
	      fontname: ptr gchar

;gboolean
gtk_font_button_get_show_style proto __cdecl \
	   font_button: ptr GtkFontButton

;void
gtk_font_button_set_show_style proto __cdecl \
	   font_button: ptr GtkFontButton,
	    show_style: gboolean

;gboolean
gtk_font_button_get_show_size proto __cdecl \
	   font_button: ptr GtkFontButton

;void
gtk_font_button_set_show_size proto __cdecl \
	   font_button: ptr GtkFontButton,
	     show_size: gboolean

G_END_DECLS

endif

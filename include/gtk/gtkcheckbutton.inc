ifndef __GTK_CHECK_BUTTON_H__
__GTK_CHECK_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktogglebutton.inc

G_BEGIN_DECLS

GTK_TYPE_CHECK_BUTTON equ <gtk_check_button_get_type>
GTK_CHECK_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CHECK_BUTTON, GtkCheckButton))>
	endm
GTK_CHECK_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CHECK_BUTTON, GtkCheckButtonClass))>
	endm
GTK_IS_CHECK_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CHECK_BUTTON))>
	endm
GTK_IS_CHECK_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CHECK_BUTTON))>
	endm
GTK_CHECK_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CHECK_BUTTON, GtkCheckButtonClass))>
	endm


GtkCheckButton		STRUC
toggle_button		GtkToggleButton <>
GtkCheckButton		ENDS

GtkCheckButtonClass	STRUC
parent_class		GtkToggleButtonClass <>
draw_indicator		proc :ptr GtkCheckButton, :ptr cairo_t
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCheckButtonClass	ENDS

;GType
gtk_check_button_get_type proto __cdecl
;GtkWidget*
gtk_check_button_new proto __cdecl
;GtkWidget*
gtk_check_button_new_with_label proto __cdecl \
		_label: ptr gchar

;GtkWidget*
gtk_check_button_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
_gtk_check_button_get_props proto __cdecl \
	  check_button: ptr GtkCheckButton,
	indicator_size: ptr gint,
     indicator_spacing: ptr gint

G_END_DECLS

endif

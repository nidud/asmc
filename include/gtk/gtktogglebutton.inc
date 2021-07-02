ifndef __GTK_TOGGLE_BUTTON_H__
__GTK_TOGGLE_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

G_BEGIN_DECLS

GTK_TYPE_TOGGLE_BUTTON equ <gtk_toggle_button_get_type>
GTK_TOGGLE_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButton))>
	endm
GTK_TOGGLE_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButtonClass))>
	endm
GTK_IS_TOGGLE_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOGGLE_BUTTON))>
	endm
GTK_IS_TOGGLE_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOGGLE_BUTTON))>
	endm
GTK_TOGGLE_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButtonClass))>
	endm

GtkToggleButton		STRUC
button			GtkButton <>
priv			ptr_t ?
GtkToggleButton		ENDS

GtkToggleButtonClass	STRUC
parent_class		GtkButtonClass <>
toggled			proc :ptr GtkToggleButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToggleButtonClass	ENDS


;GType
gtk_toggle_button_get_type proto __cdecl

;GtkWidget*
gtk_toggle_button_new proto __cdecl
;GtkWidget*
gtk_toggle_button_new_with_label proto __cdecl \
		_label: ptr gchar

;GtkWidget*
gtk_toggle_button_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
gtk_toggle_button_set_mode proto __cdecl \
	 toggle_button: ptr GtkToggleButton,
	draw_indicator: gboolean

;gboolean
gtk_toggle_button_get_mode proto __cdecl \
	 toggle_button: ptr GtkToggleButton

;void
gtk_toggle_button_set_active proto __cdecl \
	 toggle_button: ptr GtkToggleButton,
	     is_active: gboolean

;gboolean
gtk_toggle_button_get_active proto __cdecl \
	 toggle_button: ptr GtkToggleButton

;void
gtk_toggle_button_toggled proto __cdecl \
	 toggle_button: ptr GtkToggleButton

;void
gtk_toggle_button_set_inconsistent proto __cdecl \
	 toggle_button: ptr GtkToggleButton,
	       setting: gboolean

;gboolean
gtk_toggle_button_get_inconsistent proto __cdecl \
	 toggle_button: ptr GtkToggleButton

G_END_DECLS

endif

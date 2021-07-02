ifndef __GTK_SCALE_BUTTON_H__
__GTK_SCALE_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

G_BEGIN_DECLS

GTK_TYPE_SCALE_BUTTON equ <gtk_scale_button_get_type>
GTK_SCALE_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButton))>
	endm
GTK_SCALE_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))>
	endm
GTK_IS_SCALE_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCALE_BUTTON))>
	endm
GTK_IS_SCALE_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCALE_BUTTON))>
	endm
GTK_SCALE_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))>
	endm

GtkScaleButton		STRUC
parent			GtkButton <>
priv			ptr_t ?
GtkScaleButton		ENDS

GtkScaleButtonClass	STRUC
parent_class		GtkButtonClass <>
value_changed		proc :ptr GtkScaleButton, :gdouble
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkScaleButtonClass	ENDS

;GType
gtk_scale_button_get_type proto __cdecl
;GtkWidget
gtk_scale_button_new proto __cdecl \
		  size: GtkIconSize,
		   min: gdouble,
		   max: gdouble,
		  step: gdouble,
		 icons: ptr gchar

;void
gtk_scale_button_set_icons proto __cdecl \
		button: ptr GtkScaleButton,
		 icons: ptr gchar

;gdouble
gtk_scale_button_get_value proto __cdecl \
		button: ptr GtkScaleButton

;void
gtk_scale_button_set_value proto __cdecl \
		button: ptr GtkScaleButton,
		 value: gdouble

;GtkAdjustment
gtk_scale_button_get_adjustment proto __cdecl \
		button: ptr GtkScaleButton

;void
gtk_scale_button_set_adjustment proto __cdecl \
		button: ptr GtkScaleButton,
	    adjustment: ptr GtkAdjustment

;GtkWidget
gtk_scale_button_get_plus_button proto __cdecl \
		button: ptr GtkScaleButton

;GtkWidget
gtk_scale_button_get_minus_button proto __cdecl \
		button: ptr GtkScaleButton

;GtkWidget
gtk_scale_button_get_popup proto __cdecl \
		button: ptr GtkScaleButton

G_END_DECLS

endif

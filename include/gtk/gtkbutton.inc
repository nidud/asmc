ifndef __GTK_BUTTON_H__
__GTK_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc
include gtk/gtkimage.inc

G_BEGIN_DECLS

GTK_TYPE_BUTTON equ <gtk_button_get_type>
GTK_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BUTTON, GtkButton))>
	endm
GTK_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BUTTON, GtkButtonClass))>
	endm
GTK_IS_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUTTON))>
	endm
GTK_IS_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BUTTON))>
	endm
GTK_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BUTTON, GtkButtonClass))>
	endm

GtkButton		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkButton		ENDS

GtkButtonClass		STRUC
parent_class		GtkBinClass <>
pressed			proc :ptr GtkButton
released		proc :ptr GtkButton
clicked			proc :ptr GtkButton
_enter			proc :ptr GtkButton
_leave			proc :ptr GtkButton
activate		proc :ptr GtkButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkButtonClass		ENDS

;GType
gtk_button_get_type proto __cdecl
;GtkWidget*
gtk_button_new proto __cdecl
;GtkWidget*
gtk_button_new_with_label proto __cdecl \
		 _label: ptr gchar

;GtkWidget*
gtk_button_new_from_icon_name proto __cdecl \
	     icon_name: ptr gchar,
		  size: GtkIconSize

;GtkWidget*
gtk_button_new_from_stock proto __cdecl \
	      stock_id: ptr gchar

;GtkWidget*
gtk_button_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
gtk_button_clicked proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_pressed proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_released proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_enter proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_leave proto __cdecl \
		button: ptr GtkButton


;void
gtk_button_set_relief proto __cdecl \
		button: ptr GtkButton,
		relief: GtkReliefStyle

;GtkReliefStyle
gtk_button_get_relief proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_label proto __cdecl \
		button: ptr GtkButton,
		_label: ptr gchar

;const
gtk_button_get_label proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_use_underline proto __cdecl \
		button: ptr GtkButton,
	 use_underline: gboolean

;gboolean
gtk_button_get_use_underline proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_use_stock proto __cdecl \
		button: ptr GtkButton,
	     use_stock: gboolean

;gboolean
gtk_button_get_use_stock proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_focus_on_click proto __cdecl \
		button: ptr GtkButton,
	focus_on_click: gboolean

;gboolean
gtk_button_get_focus_on_click proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_alignment proto __cdecl \
		button: ptr GtkButton,
		xalign: gfloat,
		yalign: gfloat

;void
gtk_button_get_alignment proto __cdecl \
		button: ptr GtkButton,
		xalign: ptr gfloat,
		yalign: ptr gfloat

;void
gtk_button_set_image proto __cdecl \
		button: ptr GtkButton,
		 image: ptr GtkWidget

;GtkWidget*
gtk_button_get_image proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_image_position proto __cdecl \
		button: ptr GtkButton,
	      position: GtkPositionType

;GtkPositionType
gtk_button_get_image_position proto __cdecl \
		button: ptr GtkButton

;void
gtk_button_set_always_show_image proto __cdecl \
		button: ptr GtkButton,
	   always_show: gboolean

;gboolean
gtk_button_get_always_show_image proto __cdecl \
		button: ptr GtkButton


;GdkWindow*
gtk_button_get_event_window proto __cdecl \
		button: ptr GtkButton

G_END_DECLS

endif

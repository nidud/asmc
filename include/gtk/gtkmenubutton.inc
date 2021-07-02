ifndef __GTK_MENU_BUTTON_H__
__GTK_MENU_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktogglebutton.inc
include gtk/gtkmenu.inc
include gtk/gtkpopover.inc

G_BEGIN_DECLS

GTK_TYPE_MENU_BUTTON equ <gtk_menu_button_get_type>
GTK_MENU_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU_BUTTON, GtkMenuButton))>
	endm
GTK_MENU_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MENU_BUTTON, GtkMenuButtonClass))>
	endm
GTK_IS_MENU_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU_BUTTON))>
	endm
GTK_IS_MENU_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MENU_BUTTON))>
	endm
GTK_MENU_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MENU_BUTTON, GtkMenuButtonClass))>
	endm

GtkMenuButton		STRUC
parent			GtkToggleButton <>
priv			ptr_t ?
GtkMenuButton		ENDS

GtkMenuButtonClass	STRUC
parent_class		GtkToggleButtonClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuButtonClass	ENDS

;GType
gtk_menu_button_get_type proto __cdecl
;GtkWidget
gtk_menu_button_new proto __cdecl

;void
gtk_menu_button_set_popup proto __cdecl \
	   menu_button: ptr GtkMenuButton,
		  menu: ptr GtkWidget

;GtkMenu
gtk_menu_button_get_popup proto __cdecl \
	   menu_button: ptr GtkMenuButton


;void
gtk_menu_button_set_popover proto __cdecl \
	   menu_button: ptr GtkMenuButton,
	       popover: ptr GtkWidget

;GtkPopover
gtk_menu_button_get_popover proto __cdecl \
	   menu_button: ptr GtkMenuButton


;void
gtk_menu_button_set_direction proto __cdecl \
	   menu_button: ptr GtkMenuButton,
	     direction: GtkArrowType

;GtkArrowType
gtk_menu_button_get_direction proto __cdecl \
	   menu_button: ptr GtkMenuButton


;void
gtk_menu_button_set_menu_model proto __cdecl \
	   menu_button: ptr GtkMenuButton,
	    menu_model: ptr GMenuModel

;GMenuModel
gtk_menu_button_get_menu_model proto __cdecl \
	   menu_button: ptr GtkMenuButton


;void
gtk_menu_button_set_align_widget proto __cdecl \
	   menu_button: ptr GtkMenuButton,
	  align_widget: ptr GtkWidget

;GtkWidget
gtk_menu_button_get_align_widget proto __cdecl \
	   menu_button: ptr GtkMenuButton


;void
gtk_menu_button_set_use_popover proto __cdecl \
	   menu_button: ptr GtkMenuButton,
	   use_popover: gboolean


;gboolean
gtk_menu_button_get_use_popover proto __cdecl \
	   menu_button: ptr GtkMenuButton

G_END_DECLS

endif

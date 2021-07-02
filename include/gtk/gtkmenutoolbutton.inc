ifndef __GTK_MENU_TOOL_BUTTON_H__
__GTK_MENU_TOOL_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmenu.inc
include gtk/gtktoolbutton.inc

G_BEGIN_DECLS

GTK_TYPE_MENU_TOOL_BUTTON equ <gtk_menu_tool_button_get_type>
GTK_MENU_TOOL_BUTTON macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_MENU_TOOL_BUTTON, GtkMenuToolButton))>
	endm
GTK_MENU_TOOL_BUTTON_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST((k), GTK_TYPE_MENU_TOOL_BUTTON, GtkMenuToolButtonClass))>
	endm
GTK_IS_MENU_TOOL_BUTTON macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_MENU_TOOL_BUTTON))>
	endm
GTK_IS_MENU_TOOL_BUTTON_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_MENU_TOOL_BUTTON))>
	endm
GTK_MENU_TOOL_BUTTON_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_MENU_TOOL_BUTTON, GtkMenuToolButtonClass))>
	endm

GtkMenuToolButton	STRUC
parent			GtkToolButton <>
priv			ptr_t ?
GtkMenuToolButton	ENDS

GtkMenuToolButtonClass	STRUC
parent_class		GtkToolButtonClass <>
show_menu		proc :ptr GtkMenuToolButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuToolButtonClass	ENDS

;GType
gtk_menu_tool_button_get_type proto __cdecl
;GtkToolItem
gtk_menu_tool_button_new proto __cdecl \
	   icon_widget: ptr GtkWidget,
		_label: ptr gchar

;GtkToolItem
gtk_menu_tool_button_new_from_stock proto __cdecl \
	      stock_id: ptr gchar


;void
gtk_menu_tool_button_set_menu proto __cdecl \
		button: ptr GtkMenuToolButton,
		  menu: ptr GtkWidget

;GtkWidget
gtk_menu_tool_button_get_menu proto __cdecl \
		button: ptr GtkMenuToolButton

;void
gtk_menu_tool_button_set_arrow_tooltip_text proto __cdecl \
		button: ptr GtkMenuToolButton,
		  text: ptr gchar

;void
gtk_menu_tool_button_set_arrow_tooltip_markup proto __cdecl \
		button: ptr GtkMenuToolButton,
		markup: ptr gchar

G_END_DECLS

endif

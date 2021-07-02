ifndef __GTK_TOOL_BUTTON_H__
__GTK_TOOL_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktoolitem.inc

G_BEGIN_DECLS

GTK_TYPE_TOOL_BUTTON equ <gtk_tool_button_get_type>
GTK_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOOL_BUTTON, GtkToolButton))>
	endm
GTK_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOOL_BUTTON, GtkToolButtonClass))>
	endm
GTK_IS_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOOL_BUTTON))>
	endm
GTK_IS_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOOL_BUTTON))>
	endm
GTK_TOOL_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_TOOL_BUTTON, GtkToolButtonClass))>
	endm

GtkToolButton		STRUC
parent			GtkToolItem <>
priv			ptr_t ?
GtkToolButton		ENDS

GtkToolButtonClass	STRUC
parent_class		GtkToolItemClass <>
button_type		GType ?
clicked			proc :ptr GtkToolButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToolButtonClass	ENDS

;GType
gtk_tool_button_get_type proto __cdecl
;GtkToolItem
gtk_tool_button_new proto __cdecl \
	   icon_widget: ptr GtkWidget,
		_label: ptr gchar

;GtkToolItem
gtk_tool_button_new_from_stock proto __cdecl \
	      stock_id: ptr gchar

;void
gtk_tool_button_set_label proto __cdecl \
		button: ptr GtkToolButton,
		_label: ptr gchar
;const
gtk_tool_button_get_label proto __cdecl \
		button: ptr GtkToolButton

;void
gtk_tool_button_set_use_underline proto __cdecl \
		button: ptr GtkToolButton,
	 use_underline: gboolean

;gboolean
gtk_tool_button_get_use_underline proto __cdecl \
		button: ptr GtkToolButton

;void
gtk_tool_button_set_stock_id proto __cdecl \
		button: ptr GtkToolButton,
	      stock_id: ptr gchar

;const
gtk_tool_button_get_stock_id proto __cdecl \
		button: ptr GtkToolButton

;void
gtk_tool_button_set_icon_name proto __cdecl \
		button: ptr GtkToolButton,
	     icon_name: ptr gchar

;const
gtk_tool_button_get_icon_name proto __cdecl \
		button: ptr GtkToolButton

;void
gtk_tool_button_set_icon_widget proto __cdecl \
		button: ptr GtkToolButton,
	   icon_widget: ptr GtkWidget

;GtkWidget
gtk_tool_button_get_icon_widget proto __cdecl \
		button: ptr GtkToolButton

;void
gtk_tool_button_set_label_widget proto __cdecl \
		button: ptr GtkToolButton,
	  label_widget: ptr GtkWidget

;GtkWidget
gtk_tool_button_get_label_widget proto __cdecl \
		button: ptr GtkToolButton

;GtkWidget *
_gtk_tool_button_get_button proto __cdecl \
		button: ptr GtkToolButton

G_END_DECLS

endif

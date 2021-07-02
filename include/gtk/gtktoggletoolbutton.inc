ifndef __GTK_TOGGLE_TOOL_BUTTON_H__
__GTK_TOGGLE_TOOL_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktoolbutton.inc

G_BEGIN_DECLS

GTK_TYPE_TOGGLE_TOOL_BUTTON equ <gtk_toggle_tool_button_get_type>
GTK_TOGGLE_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOGGLE_TOOL_BUTTON, GtkToggleToolButton))>
	endm
GTK_TOGGLE_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOGGLE_TOOL_BUTTON, GtkToggleToolButtonClass))>
	endm
GTK_IS_TOGGLE_TOOL_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOGGLE_TOOL_BUTTON))>
	endm
GTK_IS_TOGGLE_TOOL_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOGGLE_TOOL_BUTTON))>
	endm
GTK_TOGGLE_TOOL_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_TOGGLE_TOOL_BUTTON, GtkToggleToolButtonClass))>
	endm

GtkToggleToolButton	STRUC
parent			GtkToolButton <>
priv			ptr_t ?
GtkToggleToolButton	ENDS

GtkToggleToolButtonClass STRUC
parent_class		GtkToolButtonClass <>
toggled			proc :ptr GtkToggleToolButton
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToggleToolButtonClass ENDS

;GType
gtk_toggle_tool_button_get_type proto __cdecl
;GtkToolItem
gtk_toggle_tool_button_new proto __cdecl
;GtkToolItem
gtk_toggle_tool_button_new_from_stock proto __cdecl \
	      stock_id: ptr gchar

;void
gtk_toggle_tool_button_set_active proto __cdecl \
		button: ptr GtkToggleToolButton,
	     is_active: gboolean

;gboolean
gtk_toggle_tool_button_get_active proto __cdecl \
		button: ptr GtkToggleToolButton

G_END_DECLS

endif

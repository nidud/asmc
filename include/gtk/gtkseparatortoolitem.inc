ifndef __GTK_SEPARATOR_TOOL_ITEM_H__
__GTK_SEPARATOR_TOOL_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktoolitem.inc

G_BEGIN_DECLS

GTK_TYPE_SEPARATOR_TOOL_ITEM equ <gtk_separator_tool_item_get_type>
GTK_SEPARATOR_TOOL_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEPARATOR_TOOL_ITEM, GtkSeparatorToolItem))>
	endm
GTK_SEPARATOR_TOOL_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SEPARATOR_TOOL_ITEM, GtkSeparatorToolItemClass))>
	endm
GTK_IS_SEPARATOR_TOOL_ITEM macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEPARATOR_TOOL_ITEM))>
	endm
GTK_IS_SEPARATOR_TOOL_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SEPARATOR_TOOL_ITEM))>
	endm
GTK_SEPARATOR_TOOL_ITEM_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_SEPARATOR_TOOL_ITEM, GtkSeparatorToolItemClass))>
	endm

GtkSeparatorToolItem	STRUC
parent			GtkToolItem <>
priv			ptr_t ?
GtkSeparatorToolItem	ENDS

GtkSeparatorToolItemClass STRUC
parent_class		GtkToolItemClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSeparatorToolItemClass ENDS

;GType
gtk_separator_tool_item_get_type proto __cdecl
;GtkToolItem
gtk_separator_tool_item_new proto __cdecl

;gboolean
gtk_separator_tool_item_get_draw proto __cdecl \
		  item: ptr GtkSeparatorToolItem

;void
gtk_separator_tool_item_set_draw proto __cdecl \
		  item: ptr GtkSeparatorToolItem,
		  draw: gboolean

G_END_DECLS

endif

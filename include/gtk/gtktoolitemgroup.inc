ifndef __GTK_TOOL_ITEM_GROUP_H__
__GTK_TOOL_ITEM_GROUP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
include gtk/gtktoolitem.inc

G_BEGIN_DECLS

GTK_TYPE_TOOL_ITEM_GROUP equ <gtk_tool_item_group_get_type>
GTK_TOOL_ITEM_GROUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST (obj, GTK_TYPE_TOOL_ITEM_GROUP, GtkToolItemGroup))>
	endm
GTK_TOOL_ITEM_GROUP_CLASS macro cls
	exitm<(G_TYPE_CHECK_CLASS_CAST (cls, GTK_TYPE_TOOL_ITEM_GROUP, GtkToolItemGroupClass))>
	endm
GTK_IS_TOOL_ITEM_GROUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE (obj, GTK_TYPE_TOOL_ITEM_GROUP))>
	endm
GTK_IS_TOOL_ITEM_GROUP_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_TYPE (obj, GTK_TYPE_TOOL_ITEM_GROUP))>
	endm
GTK_TOOL_ITEM_GROUP_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TOOL_ITEM_GROUP, GtkToolItemGroupClass))>
	endm

GtkToolItemGroup	STRUC
parent_instance		GtkContainer <>
priv			ptr_t ?
GtkToolItemGroup	ENDS

GtkToolItemGroupClass	STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToolItemGroupClass	ENDS

;GType
gtk_tool_item_group_get_type proto __cdecl
;GtkWidget*
gtk_tool_item_group_new proto __cdecl \
		_label: ptr gchar


;void
gtk_tool_item_group_set_label proto __cdecl \
		_group: ptr GtkToolItemGroup,
		_label: ptr gchar

;void
gtk_tool_item_group_set_label_widget proto __cdecl \
		_group: ptr GtkToolItemGroup,
	  label_widget: ptr GtkWidget

;void
gtk_tool_item_group_set_collapsed proto __cdecl \
		_group: ptr GtkToolItemGroup,
	     collapsed: gboolean

;void
gtk_tool_item_group_set_ellipsize proto __cdecl \
		_group: ptr GtkToolItemGroup,
	     ellipsize: int_t;PangoEllipsizeMode

;void
gtk_tool_item_group_set_header_relief proto __cdecl \
		_group: ptr GtkToolItemGroup,
		 style: GtkReliefStyle


;const
gtk_tool_item_group_get_label proto __cdecl \
		_group: ptr GtkToolItemGroup

;GtkWidget
gtk_tool_item_group_get_label_widget proto __cdecl \
		_group: ptr GtkToolItemGroup

;gboolean
gtk_tool_item_group_get_collapsed proto __cdecl \
		_group: ptr GtkToolItemGroup

;PangoEllipsizeMode
gtk_tool_item_group_get_ellipsize proto __cdecl \
		_group: ptr GtkToolItemGroup

;GtkReliefStyle
gtk_tool_item_group_get_header_relief proto __cdecl \
		_group: ptr GtkToolItemGroup


;void
gtk_tool_item_group_insert proto __cdecl \
		_group: ptr GtkToolItemGroup,
		  item: ptr GtkToolItem,
	      position: gint

;void
gtk_tool_item_group_set_item_position proto __cdecl \
		_group: ptr GtkToolItemGroup,
		  item: ptr GtkToolItem,
	      position: gint

;gint
gtk_tool_item_group_get_item_position proto __cdecl \
		_group: ptr GtkToolItemGroup,
		  item: ptr GtkToolItem


;guint
gtk_tool_item_group_get_n_items proto __cdecl \
		_group: ptr GtkToolItemGroup

;GtkToolItem*
gtk_tool_item_group_get_nth_item proto __cdecl \
		_group: ptr GtkToolItemGroup,
		 index: guint

;GtkToolItem*
gtk_tool_item_group_get_drop_item proto __cdecl \
		_group: ptr GtkToolItemGroup,
		     x: gint,
		     y: gint

G_END_DECLS

endif

ifndef __GTK_TOOL_ITEM_H__
__GTK_TOOL_ITEM_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc
include gtk/gtkmenuitem.inc
include gtk/gtksizegroup.inc

G_BEGIN_DECLS

GTK_TYPE_TOOL_ITEM equ <gtk_tool_item_get_type>
GTK_TOOL_ITEM macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_TOOL_ITEM, GtkToolItem))>
	endm
GTK_TOOL_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOOL_ITEM, GtkToolItemClass))>
	endm
GTK_IS_TOOL_ITEM macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_TOOL_ITEM))>
	endm
GTK_IS_TOOL_ITEM_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOOL_ITEM))>
	endm
GTK_TOOL_ITEM_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS((o), GTK_TYPE_TOOL_ITEM, GtkToolItemClass))>
	endm

GtkToolItem		STRUC
parent			GtkBin <>
priv			ptr_t ?
GtkToolItem		ENDS

GtkToolItemClass	STRUC
parent_class		GtkBinClass <>
create_menu_proxy	proc :ptr GtkToolItem
toolbar_reconfigured	proc :ptr GtkToolItem
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToolItemClass	ENDS


;GType
gtk_tool_item_get_type proto __cdecl
;GtkToolItem
gtk_tool_item_new proto __cdecl

;void
gtk_tool_item_set_homogeneous proto __cdecl \
	     tool_item: ptr GtkToolItem,
	   homogeneous: gboolean

;gboolean
gtk_tool_item_get_homogeneous proto __cdecl \
	     tool_item: ptr GtkToolItem


;void
gtk_tool_item_set_expand proto __cdecl \
	     tool_item: ptr GtkToolItem,
		expand: gboolean

;gboolean
gtk_tool_item_get_expand proto __cdecl \
	     tool_item: ptr GtkToolItem

;void
gtk_tool_item_set_tooltip_text proto __cdecl \
	     tool_item: ptr GtkToolItem,
		  text: ptr gchar

;void
gtk_tool_item_set_tooltip_markup proto __cdecl \
	     tool_item: ptr GtkToolItem,
		markup: ptr gchar


;void
gtk_tool_item_set_use_drag_window proto __cdecl \
	     tool_item: ptr GtkToolItem,
       use_drag_window: gboolean

;gboolean
gtk_tool_item_get_use_drag_window proto __cdecl \
	     tool_item: ptr GtkToolItem


;void
gtk_tool_item_set_visible_horizontal proto __cdecl \
	     tool_item: ptr GtkToolItem,
    visible_horizontal: gboolean

;gboolean
gtk_tool_item_get_visible_horizontal proto __cdecl \
	     tool_item: ptr GtkToolItem


;void
gtk_tool_item_set_visible_vertical proto __cdecl \
	     tool_item: ptr GtkToolItem,
      visible_vertical: gboolean

;gboolean
gtk_tool_item_get_visible_vertical proto __cdecl \
	     tool_item: ptr GtkToolItem


;gboolean
gtk_tool_item_get_is_important proto __cdecl \
	     tool_item: ptr GtkToolItem

;void
gtk_tool_item_set_is_important proto __cdecl \
	     tool_item: ptr GtkToolItem,
	  is_important: gboolean


;PangoEllipsizeMode
gtk_tool_item_get_ellipsize_mode proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkIconSize
gtk_tool_item_get_icon_size proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkOrientation
gtk_tool_item_get_orientation proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkToolbarStyle
gtk_tool_item_get_toolbar_style proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkReliefStyle
gtk_tool_item_get_relief_style proto __cdecl \
	     tool_item: ptr GtkToolItem

;gfloat
gtk_tool_item_get_text_alignment proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkOrientation
gtk_tool_item_get_text_orientation proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkSizeGroup
gtk_tool_item_get_text_size_group proto __cdecl \
	     tool_item: ptr GtkToolItem


;GtkWidget
gtk_tool_item_retrieve_proxy_menu_item proto __cdecl \
	     tool_item: ptr GtkToolItem

;GtkWidget
gtk_tool_item_get_proxy_menu_item proto __cdecl \
	     tool_item: ptr GtkToolItem,
	  menu_item_id: ptr gchar

;void
gtk_tool_item_set_proxy_menu_item proto __cdecl \
	     tool_item: ptr GtkToolItem,
	  menu_item_id: ptr gchar,
	     menu_item: ptr GtkWidget

;void
gtk_tool_item_rebuild_menu proto __cdecl \
	     tool_item: ptr GtkToolItem

;void
gtk_tool_item_toolbar_reconfigured proto __cdecl \
	     tool_item: ptr GtkToolItem

_gtk_tool_item_create_menu_proxy proto __cdecl \
	     tool_item: ptr GtkToolItem

G_END_DECLS

endif

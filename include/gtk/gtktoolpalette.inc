ifndef __GTK_TOOL_PALETTE_H__
__GTK_TOOL_PALETTE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
include gtk/gtkdnd.inc
include gtk/gtktoolitem.inc

G_BEGIN_DECLS

GTK_TYPE_TOOL_PALETTE equ <gtk_tool_palette_get_type>
GTK_TOOL_PALETTE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST (obj, GTK_TYPE_TOOL_PALETTE, GtkToolPalette))>
	endm
GTK_TOOL_PALETTE_CLASS macro cls
	exitm<(G_TYPE_CHECK_CLASS_CAST (cls, GTK_TYPE_TOOL_PALETTE, GtkToolPaletteClass))>
	endm
GTK_IS_TOOL_PALETTE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE (obj, GTK_TYPE_TOOL_PALETTE))>
	endm
GTK_IS_TOOL_PALETTE_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_TYPE (obj, GTK_TYPE_TOOL_PALETTE))>
	endm
GTK_TOOL_PALETTE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TOOL_PALETTE, GtkToolPaletteClass))>
	endm

.enum GtkToolPaletteDragTargets {
  GTK_TOOL_PALETTE_DRAG_ITEMS  = (1 shl 0),
  GTK_TOOL_PALETTE_DRAG_GROUPS = (1 shl 1)
}

GtkToolPalette		STRUC
parent_instance		GtkContainer <>
priv			ptr_t ?
GtkToolPalette		ENDS

GtkToolPaletteClass	STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToolPaletteClass	ENDS

;GType
gtk_tool_palette_get_type proto __cdecl
;GtkWidget*
gtk_tool_palette_new proto __cdecl

;void
gtk_tool_palette_set_group_position proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup,
	      position: gint

;void
gtk_tool_palette_set_exclusive proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup,
	     exclusive: gboolean

;void
gtk_tool_palette_set_expand proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup,
		expand: gboolean


;gint
gtk_tool_palette_get_group_position proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup

;gboolean
gtk_tool_palette_get_exclusive proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup

;gboolean
gtk_tool_palette_get_expand proto __cdecl \
	       palette: ptr GtkToolPalette,
		_group: ptr GtkToolItemGroup


;void
gtk_tool_palette_set_icon_size proto __cdecl \
	       palette: ptr GtkToolPalette,
	     icon_size: GtkIconSize

;void
gtk_tool_palette_unset_icon_size proto __cdecl \
	       palette: ptr GtkToolPalette

;void
gtk_tool_palette_set_style proto __cdecl \
	       palette: ptr GtkToolPalette,
		 style: GtkToolbarStyle

;void
gtk_tool_palette_unset_style proto __cdecl \
	       palette: ptr GtkToolPalette


;GtkIconSize
gtk_tool_palette_get_icon_size proto __cdecl \
	       palette: ptr GtkToolPalette

;GtkToolbarStyle
gtk_tool_palette_get_style proto __cdecl \
	       palette: ptr GtkToolPalette


;GtkToolItem*
gtk_tool_palette_get_drop_item proto __cdecl \
	       palette: ptr GtkToolPalette,
		     x: gint,
		     y: gint

;GtkToolItemGroup*
gtk_tool_palette_get_drop_group proto __cdecl \
	       palette: ptr GtkToolPalette,
		     x: gint,
		     y: gint

;GtkWidget*
gtk_tool_palette_get_drag_item proto __cdecl \
	       palette: ptr GtkToolPalette,
	     selection: ptr GtkSelectionData


;void
gtk_tool_palette_set_drag_source proto __cdecl \
	       palette: ptr GtkToolPalette,
	       targets: GtkToolPaletteDragTargets

;void
gtk_tool_palette_add_drag_dest proto __cdecl \
	       palette: ptr GtkToolPalette,
		widget: ptr GtkWidget,
		 flags: GtkDestDefaults,
	       targets: GtkToolPaletteDragTargets,
	       actions: GdkDragAction



;GtkAdjustment*
gtk_tool_palette_get_hadjustment proto __cdecl \
	       palette: ptr GtkToolPalette

;GtkAdjustment*
gtk_tool_palette_get_vadjustment proto __cdecl \
	       palette: ptr GtkToolPalette


gtk_tool_palette_get_drag_target_item proto __cdecl
gtk_tool_palette_get_drag_target_group proto __cdecl

G_END_DECLS

endif

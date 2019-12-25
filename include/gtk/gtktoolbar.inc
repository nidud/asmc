ifndef __GTK_TOOLBAR_H__
__GTK_TOOLBAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
include gtk/gtktoolitem.inc

G_BEGIN_DECLS

GTK_TYPE_TOOLBAR equ <gtk_toolbar_get_type>
GTK_TOOLBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOOLBAR, GtkToolbar))>
	endm
GTK_TOOLBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOOLBAR, GtkToolbarClass))>
	endm
GTK_IS_TOOLBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOOLBAR))>
	endm
GTK_IS_TOOLBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOOLBAR))>
	endm
GTK_TOOLBAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TOOLBAR, GtkToolbarClass))>
	endm

.enum GtkToolbarSpaceStyle {
  GTK_TOOLBAR_SPACE_EMPTY,
  GTK_TOOLBAR_SPACE_LINE
}

GtkToolbar		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkToolbar		ENDS

GtkToolbarClass		STRUC
parent_class		GtkContainerClass <>
orientation_changed	proc :ptr GtkToolbar, :GtkOrientation
style_changed		proc :ptr GtkToolbar, :GtkToolbarStyle
popup_context_menu	proc :ptr GtkToolbar, :gint, :gint, :gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkToolbarClass		ENDS

;GType
gtk_toolbar_get_type proto __cdecl
;GtkWidget
gtk_toolbar_new proto __cdecl

;void
gtk_toolbar_insert proto __cdecl \
	       toolbar: ptr GtkToolbar,
		  item: ptr GtkToolItem,
		   pos: gint


;gint
gtk_toolbar_get_item_index proto __cdecl \
	       toolbar: ptr GtkToolbar,
		  item: ptr GtkToolItem

;gint
gtk_toolbar_get_n_items proto __cdecl \
	       toolbar: ptr GtkToolbar

;GtkToolItem
gtk_toolbar_get_nth_item proto __cdecl \
	       toolbar: ptr GtkToolbar,
		     n: gint


;gboolean
gtk_toolbar_get_show_arrow proto __cdecl \
	       toolbar: ptr GtkToolbar

;void
gtk_toolbar_set_show_arrow proto __cdecl \
	       toolbar: ptr GtkToolbar,
	    show_arrow: gboolean


;GtkToolbarStyle
gtk_toolbar_get_style proto __cdecl \
	       toolbar: ptr GtkToolbar

;void
gtk_toolbar_set_style proto __cdecl \
	       toolbar: ptr GtkToolbar,
		 style: GtkToolbarStyle

;void
gtk_toolbar_unset_style proto __cdecl \
	       toolbar: ptr GtkToolbar


;GtkIconSize
gtk_toolbar_get_icon_size proto __cdecl \
	       toolbar: ptr GtkToolbar

;void
gtk_toolbar_set_icon_size proto __cdecl \
	       toolbar: ptr GtkToolbar,
	     icon_size: GtkIconSize

;void
gtk_toolbar_unset_icon_size proto __cdecl \
	       toolbar: ptr GtkToolbar


;GtkReliefStyle
gtk_toolbar_get_relief_style proto __cdecl \
	       toolbar: ptr GtkToolbar

;gint
gtk_toolbar_get_drop_index proto __cdecl \
	       toolbar: ptr GtkToolbar,
		     x: gint,
		     y: gint

;void
gtk_toolbar_set_drop_highlight_item proto __cdecl \
	       toolbar: ptr GtkToolbar,
	     tool_item: ptr GtkToolItem,
		index_: gint

G_END_DECLS

endif

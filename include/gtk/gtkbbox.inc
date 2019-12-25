ifndef __GTK_BUTTON_BOX_H__
__GTK_BUTTON_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc

G_BEGIN_DECLS

GTK_TYPE_BUTTON_BOX equ <gtk_button_box_get_type>
GTK_BUTTON_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BUTTON_BOX, GtkButtonBox))>
	endm
GTK_BUTTON_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BUTTON_BOX, GtkButtonBoxClass))>
	endm
GTK_IS_BUTTON_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUTTON_BOX))>
	endm
GTK_IS_BUTTON_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BUTTON_BOX))>
	endm
GTK_BUTTON_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BUTTON_BOX, GtkButtonBoxClass))>
	endm

GtkButtonBox		STRUC
box			GtkBox <>
priv			ptr_t ?
GtkButtonBox		ENDS

GtkButtonBoxClass	STRUC
parent_class		GtkBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkButtonBoxClass	ENDS

.enum GtkButtonBoxStyle {
  GTK_BUTTONBOX_SPREAD = 1,
  GTK_BUTTONBOX_EDGE,
  GTK_BUTTONBOX_START,
  GTK_BUTTONBOX_END,
  GTK_BUTTONBOX_CENTER,
  GTK_BUTTONBOX_EXPAND
}

;GType
gtk_button_box_get_type proto __cdecl
;GtkWidget
gtk_button_box_new proto __cdecl \
	   orientation: GtkOrientation

;GtkButtonBoxStyle
gtk_button_box_get_layout proto __cdecl \
		widget: ptr GtkButtonBox

;void
gtk_button_box_set_layout proto __cdecl \
		widget: ptr GtkButtonBox,
	  layout_style: GtkButtonBoxStyle

;gboolean
gtk_button_box_get_child_secondary proto __cdecl \
		widget: ptr GtkButtonBox,
		 child: ptr GtkWidget

;void
gtk_button_box_set_child_secondary proto __cdecl \
		widget: ptr GtkButtonBox,
		 child: ptr GtkWidget,
	  is_secondary: gboolean

;gboolean
gtk_button_box_get_child_non_homogeneous proto __cdecl \
		widget: ptr GtkButtonBox,
		 child: ptr GtkWidget

;void
gtk_button_box_set_child_non_homogeneous proto __cdecl \
		widget: ptr GtkButtonBox,
		 child: ptr GtkWidget,
       non_homogeneous: gboolean


G_END_DECLS

endif

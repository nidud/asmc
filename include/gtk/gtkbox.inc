ifndef __GTK_BOX_H__
__GTK_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_BOX equ <gtk_box_get_type>
GTK_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BOX, GtkBox))>
	endm
GTK_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BOX, GtkBoxClass))>
	endm
GTK_IS_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BOX))>
	endm
GTK_IS_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BOX))>
	endm
GTK_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BOX, GtkBoxClass))>
	endm

GtkBox			STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkBox			ENDS

GtkBoxClass		STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkBoxClass		ENDS

;GType
gtk_box_get_type proto __cdecl
;GtkWidget*
gtk_box_new proto __cdecl \
	   orientation: GtkOrientation,
	       spacing: gint


;void
gtk_box_pack_start proto __cdecl \
		   box: ptr GtkBox,
		 child: ptr GtkWidget,
		expand: gboolean,
		  fill: gboolean,
	       padding: guint

;void
gtk_box_pack_end proto __cdecl \
		   box: ptr GtkBox,
		 child: ptr GtkWidget,
		expand: gboolean,
		  fill: gboolean,
	       padding: guint


;void
gtk_box_set_homogeneous proto __cdecl \
		   box: ptr GtkBox,
	   homogeneous: gboolean

;gboolean
gtk_box_get_homogeneous proto __cdecl \
		   box: ptr GtkBox

;void
gtk_box_set_spacing proto __cdecl \
		   box: ptr GtkBox,
	       spacing: gint

;gint
gtk_box_get_spacing proto __cdecl \
		   box: ptr GtkBox

;void
gtk_box_set_baseline_position proto __cdecl \
		   box: ptr GtkBox,
	      position: GtkBaselinePosition

;GtkBaselinePosition
gtk_box_get_baseline_position proto __cdecl \
		   box: ptr GtkBox


;void
gtk_box_reorder_child proto __cdecl \
		   box: ptr GtkBox,
		 child: ptr GtkWidget,
	      position: gint


;void
gtk_box_query_child_packing proto __cdecl \
		   box: ptr GtkBox,
		 child: ptr GtkWidget,
		expand: ptr gboolean,
		  fill: ptr gboolean,
	       padding: ptr guint,
	     pack_type: ptr GtkPackType

;void
gtk_box_set_child_packing proto __cdecl \
		   box: ptr GtkBox,
		 child: ptr GtkWidget,
		expand: gboolean,
		  fill: gboolean,
	       padding: guint,
	     pack_type: GtkPackType


;void
gtk_box_set_center_widget proto __cdecl \
		   box: ptr GtkBox,
		widget: ptr GtkWidget

;GtkWidget
gtk_box_get_center_widget proto __cdecl \
		   box: ptr GtkBox


G_END_DECLS

endif

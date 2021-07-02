ifndef __GTK_FRAME_H__
__GTK_FRAME_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_FRAME equ <gtk_frame_get_type>
GTK_FRAME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FRAME, GtkFrame))>
	endm
GTK_FRAME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FRAME, GtkFrameClass))>
	endm
GTK_IS_FRAME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FRAME))>
	endm
GTK_IS_FRAME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FRAME))>
	endm
GTK_FRAME_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FRAME, GtkFrameClass))>
	endm

GtkFrame		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkFrame		ENDS

GtkFrameClass		STRUC
parent_class		GtkBinClass <>
compute_child_allocation proc :ptr GtkFrame, :ptr GtkAllocation
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkFrameClass		ENDS

;GType
gtk_frame_get_type proto __cdecl
;GtkWidget*
gtk_frame_new proto __cdecl \
		_label: ptr gchar


;void
gtk_frame_set_label proto __cdecl \
		_frame: ptr GtkFrame,
		_label: ptr gchar

;const
gtk_frame_get_label proto __cdecl \
		_frame: ptr GtkFrame


;void
gtk_frame_set_label_widget proto __cdecl \
		_frame: ptr GtkFrame,
	  label_widget: ptr GtkWidget

;GtkWidget
gtk_frame_get_label_widget proto __cdecl \
		_frame: ptr GtkFrame

;void
gtk_frame_set_label_align proto __cdecl \
		_frame: ptr GtkFrame,
		xalign: gfloat,
		yalign: gfloat

;void
gtk_frame_get_label_align proto __cdecl \
		_frame: ptr GtkFrame,
		xalign: ptr gfloat,
		yalign: ptr gfloat

;void
gtk_frame_set_shadow_type proto __cdecl \
		_frame: ptr GtkFrame,
		  type: GtkShadowType

;GtkShadowType
gtk_frame_get_shadow_type proto __cdecl \
		_frame: ptr GtkFrame

G_END_DECLS

endif

ifndef __GTK_ASPECT_FRAME_H__
__GTK_ASPECT_FRAME_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkframe.inc

G_BEGIN_DECLS

GTK_TYPE_ASPECT_FRAME equ <gtk_aspect_frame_get_type>
GTK_ASPECT_FRAME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ASPECT_FRAME, GtkAspectFrame))>
	endm
GTK_ASPECT_FRAME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ASPECT_FRAME, GtkAspectFrameClass))>
	endm
GTK_IS_ASPECT_FRAME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ASPECT_FRAME))>
	endm
GTK_IS_ASPECT_FRAME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ASPECT_FRAME))>
	endm
GTK_ASPECT_FRAME_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ASPECT_FRAME, GtkAspectFrameClass))>
	endm

GtkAspectFrame		STRUC
_frame			GtkFrame <>
priv			ptr_t ?
GtkAspectFrame		ENDS

GtkAspectFrameClass	STRUC
parent_class		GtkFrameClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAspectFrameClass	ENDS

;GType
gtk_aspect_frame_get_type proto __cdecl
;GtkWidget*
gtk_aspect_frame_new proto __cdecl \
		_label: ptr gchar,
		xalign: gfloat,
		yalign: gfloat,
		 ratio: gfloat,
	    obey_child: gboolean

;void
gtk_aspect_frame_set proto __cdecl \
	  aspect_frame: ptr GtkAspectFrame,
		xalign: gfloat,
		yalign: gfloat,
		 ratio: gfloat,
	    obey_child: gboolean

G_END_DECLS

endif

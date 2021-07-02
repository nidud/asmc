ifndef __GTK_MISC_H__
__GTK_MISC_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc


G_BEGIN_DECLS

GTK_TYPE_MISC equ <gtk_misc_get_type>
GTK_MISC macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MISC, GtkMisc))>
	endm
GTK_MISC_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MISC, GtkMiscClass))>
	endm
GTK_IS_MISC macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MISC))>
	endm
GTK_IS_MISC_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MISC))>
	endm
GTK_MISC_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MISC, GtkMiscClass))>
	endm


GtkMisc			STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkMisc			ENDS

GtkMiscClass		STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMiscClass		ENDS

;GType
gtk_misc_get_type proto __cdecl
;void
gtk_misc_set_alignment proto __cdecl \
		  misc: ptr GtkMisc,
		xalign: gfloat,
		yalign: gfloat

;void
gtk_misc_get_alignment proto __cdecl \
		  misc: ptr GtkMisc,
		xalign: ptr gfloat,
		yalign: ptr gfloat

;void
gtk_misc_set_padding proto __cdecl \
		  misc: ptr GtkMisc,
		  xpad: gint,
		  ypad: gint

;void
gtk_misc_get_padding proto __cdecl \
		  misc: ptr GtkMisc,
		  xpad: ptr gint,
		  ypad: ptr gint


;void
_gtk_misc_get_padding_and_border proto __cdecl \
		  misc: ptr GtkMisc,
		border: ptr GtkBorder


G_END_DECLS

endif

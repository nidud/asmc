ifndef __GTK_VOLUME_BUTTON_H__
__GTK_VOLUME_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkscalebutton.inc

G_BEGIN_DECLS

GTK_TYPE_VOLUME_BUTTON equ <gtk_volume_button_get_type>
GTK_VOLUME_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VOLUME_BUTTON, GtkVolumeButton))>
	endm
GTK_VOLUME_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_VOLUME_BUTTON, GtkVolumeButtonClass))>
	endm
GTK_IS_VOLUME_BUTTON macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VOLUME_BUTTON))>
	endm
GTK_IS_VOLUME_BUTTON_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VOLUME_BUTTON))>
	endm
GTK_VOLUME_BUTTON_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VOLUME_BUTTON, GtkVolumeButtonClass))>
	endm

GtkVolumeButton		STRUC
parent			GtkScaleButton <>
GtkVolumeButton		ENDS

GtkVolumeButtonClass	STRUC
parent_class		GtkScaleButtonClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkVolumeButtonClass	ENDS

;GType
gtk_volume_button_get_type proto __cdecl
;GtkWidget*
gtk_volume_button_new proto __cdecl

G_END_DECLS

endif

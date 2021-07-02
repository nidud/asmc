ifndef __GTK_FIXED_H__
__GTK_FIXED_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_FIXED equ <gtk_fixed_get_type>
GTK_FIXED macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FIXED, GtkFixed))>
	endm
GTK_FIXED_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FIXED, GtkFixedClass))>
	endm
GTK_IS_FIXED macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FIXED))>
	endm
GTK_IS_FIXED_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FIXED))>
	endm
GTK_FIXED_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FIXED, GtkFixedClass))>
	endm

GtkFixed		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkFixed		ENDS

GtkFixedClass		STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkFixedClass		ENDS

GtkFixedChild		STRUC
widget			ptr_t ?
x			gint ?
y			gint ?
GtkFixedChild		ENDS

;GType
gtk_fixed_get_type proto __cdecl
;GtkWidget*
gtk_fixed_new proto __cdecl
;void
gtk_fixed_put proto __cdecl \
		 fixed: ptr GtkFixed,
		widget: ptr GtkWidget,
		     x: gint,
		     y: gint

;void
gtk_fixed_move proto __cdecl \
		 fixed: ptr GtkFixed,
		widget: ptr GtkWidget,
		     x: gint,
		     y: gint

G_END_DECLS

endif

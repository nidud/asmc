ifndef __GTK_BORDER_H__
__GTK_BORDER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

GTK_TYPE_BORDER		equ <gtk_border_get_type>

GtkBorder		STRUC
left			gint16 ?
right			gint16 ?
top			gint16 ?
bottom			gint16 ?
GtkBorder		ENDS

gtk_border_get_type	proto __cdecl
gtk_border_new		proto __cdecl
gtk_border_copy		proto __cdecl border_: ptr GtkBorder
gtk_border_free		proto __cdecl border_: ptr GtkBorder

endif

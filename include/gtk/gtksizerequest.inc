ifndef __GTK_SIZE_REQUEST_H__
__GTK_SIZE_REQUEST_H__ equ <>

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GtkRequestedSize	STRUC
data			gpointer ?
minimum_size		gint ?
natural_size		gint ?
GtkRequestedSize	ENDS

;gint
gtk_distribute_natural_allocation proto __cdecl \
	   extra_space: gint,
     n_requested_sizes: guint,
		 sizes: ptr GtkRequestedSize

G_END_DECLS

endif

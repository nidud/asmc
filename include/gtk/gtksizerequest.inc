ifndef __GTK_SIZE_REQUEST_H__
define __GTK_SIZE_REQUEST_H__

include gtk/gtkwidget.inc

GtkRequestedSize        struct
data                    gpointer ?
minimum_size            sdword ?
natural_size            sdword ?
GtkRequestedSize        ends

gtk_distribute_natural_allocation proto :sdword, :guint, :ptr

endif

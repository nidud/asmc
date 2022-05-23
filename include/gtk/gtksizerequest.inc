ifndef __GTK_SIZE_REQUEST_H__
define __GTK_SIZE_REQUEST_H__

include gtk/gtkwidget.inc

_GtkRequestedSize       struct
data                    gpointer ?
minimum_size            sdword ?
natural_size            sdword ?
_GtkRequestedSize       ends
GtkRequestedSize        typedef _GtkRequestedSize

gtk_distribute_natural_allocation proto :sdword, :guint, :ptr

endif

ifndef __GTK_BORDER_H__
define __GTK_BORDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

define GTK_TYPE_BORDER <gtk_border_get_type ()>

_GtkBorder              struct
left                    gint16 ?
right                   gint16 ?
top                     gint16 ?
bottom                  gint16 ?
_GtkBorder              ends
GtkBorder               typedef _GtkBorder

gtk_border_get_type proto
gtk_border_new proto
gtk_border_copy proto :ptr
gtk_border_free proto :ptr

endif

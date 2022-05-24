ifndef __GTK_MULTI_SORTER_H__
define __GTK_MULTI_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtksorter.inc

define GTK_TYPE_MULTI_SORTER <gtk_multi_sorter_get_type ()>

gtk_multi_sorter_new proto
gtk_multi_sorter_append proto :ptr, :ptr
gtk_multi_sorter_remove proto :ptr, :guint

endif

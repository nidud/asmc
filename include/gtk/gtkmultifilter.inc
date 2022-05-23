ifndef __GTK_MULTI_FILTER_H__
define __GTK_MULTI_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkfilter.inc
include gtk/gtktypes.inc

define GTK_TYPE_MULTI_FILTER <gtk_multi_filter_get_type>

gtk_multi_filter_append proto :ptr, :ptr
gtk_multi_filter_remove proto :ptr, :guint

define GTK_TYPE_ANY_FILTER <gtk_any_filter_get_type>
gtk_any_filter_new proto

define GTK_TYPE_EVERY_FILTER <gtk_every_filter_get_type>
gtk_every_filter_new proto

endif

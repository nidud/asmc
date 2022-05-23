ifndef __GTK_BOOL_FILTER_H__
define __GTK_BOOL_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtkfilter.inc

define GTK_TYPE_BOOL_FILTER <gtk_bool_filter_get_type>

gtk_bool_filter_new proto :ptr

gtk_bool_filter_get_expression proto :ptr
gtk_bool_filter_set_expression proto :ptr, :ptr
gtk_bool_filter_get_invert proto :ptr
gtk_bool_filter_set_invert proto :ptr, :gboolean

endif

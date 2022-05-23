ifndef __GTK_STRING_SORTER_H__
define __GTK_STRING_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtksorter.inc

define GTK_TYPE_STRING_SORTER <gtk_string_sorter_get_type>

gtk_string_sorter_new proto :ptr

gtk_string_sorter_get_expression proto :ptr
gtk_string_sorter_set_expression proto :ptr, :ptr
gtk_string_sorter_get_ignore_case proto :ptr
gtk_string_sorter_set_ignore_case proto :ptr, :gboolean

endif

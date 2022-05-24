ifndef __GTK_STRING_FILTER_H__
define __GTK_STRING_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkexpression.inc
include gtk/gtkfilter.inc

.enum GtkStringFilterMatchMode {
  GTK_STRING_FILTER_MATCH_MODE_EXACT,
  GTK_STRING_FILTER_MATCH_MODE_SUBSTRING,
  GTK_STRING_FILTER_MATCH_MODE_PREFIX
}

define GTK_TYPE_STRING_FILTER <gtk_string_filter_get_type ()>

gtk_string_filter_new proto :ptr
gtk_string_filter_get_search proto :ptr
gtk_string_filter_set_search proto :ptr, :ptr
gtk_string_filter_get_expression proto :ptr
gtk_string_filter_set_expression proto :ptr, :ptr
gtk_string_filter_get_ignore_case proto :ptr
gtk_string_filter_set_ignore_case proto :ptr, :gboolean
gtk_string_filter_get_match_mode proto :ptr
gtk_string_filter_set_match_mode proto :ptr, :GtkStringFilterMatchMode

endif

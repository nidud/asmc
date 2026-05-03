ifndef __GTK_CSS_ENUM_TYPES_H__
define __GTK_CSS_ENUM_TYPES_H__

if not defined (__GTK_CSS_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/css/gtkcss.h can be included directly.">
endif

include glib-object.inc
include gdk/gdkversionmacros.inc

gtk_css_parser_error_get_type proto
define GTK_TYPE_CSS_PARSER_ERROR <gtk_css_parser_error_get_type ()>
gtk_css_parser_warning_get_type proto
define GTK_TYPE_CSS_PARSER_WARNING <gtk_css_parser_warning_get_type ()>

endif




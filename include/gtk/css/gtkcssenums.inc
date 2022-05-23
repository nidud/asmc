ifndef __GTK_CSS_ENUMS_H__
define __GTK_CSS_ENUMS_H__

if not defined (__GTK_CSS_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/css/gtkcss.h can be included directly.">
endif

include glib.inc
include gdk/gdkversionmacros.inc


.enum GtkCssParserError {
  GTK_CSS_PARSER_ERROR_FAILED,
  GTK_CSS_PARSER_ERROR_SYNTAX,
  GTK_CSS_PARSER_ERROR_IMPORT,
  GTK_CSS_PARSER_ERROR_NAME,
  GTK_CSS_PARSER_ERROR_UNKNOWN_VALUE
}


.enum GtkCssParserWarning {
  GTK_CSS_PARSER_WARNING_DEPRECATED,
  GTK_CSS_PARSER_WARNING_SYNTAX,
  GTK_CSS_PARSER_WARNING_UNIMPLEMENTED
}

endif

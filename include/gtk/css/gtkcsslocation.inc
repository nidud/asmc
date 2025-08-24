ifndef __GTK_CSS_LOCATION_H__
define __GTK_CSS_LOCATION_H__

if not defined (__GTK_CSS_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/css/gtkcss.h can be included directly.">
endif

include glib.inc

GtkCssLocation          STRUC
bytes                   gsize ?
chars                   gsize ?
lines                   gsize ?
line_bytes              gsize ?
line_chars              gsize ?
GtkCssLocation          ENDS

endif

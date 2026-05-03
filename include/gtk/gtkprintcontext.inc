ifndef __GTK_PRINT_CONTEXT_H__
define __GTK_PRINT_CONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include pango/pango.inc
include gtk/gtkpagesetup.inc

define GTK_TYPE_PRINT_CONTEXT <gtk_print_context_get_type ()>
GTK_PRINT_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_CONTEXT, GtkPrintContext))>
  endm
GTK_IS_PRINT_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_CONTEXT))>
  endm

gtk_print_context_get_type proto
gtk_print_context_get_cairo_context proto :ptr
gtk_print_context_get_page_setup proto :ptr
gtk_print_context_get_width proto :ptr
gtk_print_context_get_height proto :ptr
gtk_print_context_get_dpi_x proto :ptr
gtk_print_context_get_dpi_y proto :ptr
gtk_print_context_get_hard_margins proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_print_context_get_pango_fontmap proto :ptr
gtk_print_context_create_pango_context proto :ptr
gtk_print_context_create_pango_layout proto :ptr
gtk_print_context_set_cairo_context proto :ptr, :ptr, :real8, :real8

endif

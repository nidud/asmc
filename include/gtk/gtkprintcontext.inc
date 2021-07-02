ifndef __GTK_PRINT_CONTEXT_H__
__GTK_PRINT_CONTEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;include pango/pango.inc
include gtk/gtkpagesetup.inc

G_BEGIN_DECLS

GTK_TYPE_PRINT_CONTEXT equ <gtk_print_context_get_type>
GTK_PRINT_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_CONTEXT, GtkPrintContext))>
	endm
GTK_IS_PRINT_CONTEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_CONTEXT))>
	endm

;GType
gtk_print_context_get_type proto __cdecl


;cairo_t
gtk_print_context_get_cairo_context proto __cdecl \
	       context: ptr GtkPrintContext


;GtkPageSetup
gtk_print_context_get_page_setup proto __cdecl \
	       context: ptr GtkPrintContext

;gdouble
gtk_print_context_get_width proto __cdecl \
	       context: ptr GtkPrintContext

;gdouble
gtk_print_context_get_height proto __cdecl \
	       context: ptr GtkPrintContext

;gdouble
gtk_print_context_get_dpi_x proto __cdecl \
	       context: ptr GtkPrintContext

;gdouble
gtk_print_context_get_dpi_y proto __cdecl \
	       context: ptr GtkPrintContext

;gboolean
gtk_print_context_get_hard_margins proto __cdecl \
	       context: ptr GtkPrintContext,
		   top: ptr gdouble,
		bottom: ptr gdouble,
		  left: ptr gdouble,
		 right: ptr gdouble


;PangoFontMap
gtk_print_context_get_pango_fontmap proto __cdecl \
	       context: ptr GtkPrintContext

;PangoContext
gtk_print_context_create_pango_context proto __cdecl \
	       context: ptr GtkPrintContext

;PangoLayout
gtk_print_context_create_pango_layout proto __cdecl \
	       context: ptr GtkPrintContext


;void
gtk_print_context_set_cairo_context proto __cdecl \
	       context: ptr GtkPrintContext,
		    cr: ptr cairo_t,
		 dpi_x: double,
		 dpi_y: double


G_END_DECLS

endif

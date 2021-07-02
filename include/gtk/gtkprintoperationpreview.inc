ifndef __GTK_PRINT_OPERATION_PREVIEW_H__
__GTK_PRINT_OPERATION_PREVIEW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;include cairo.inc
include gtk/gtkprintcontext.inc

G_BEGIN_DECLS

GTK_TYPE_PRINT_OPERATION_PREVIEW equ <gtk_print_operation_preview_get_type>
GTK_PRINT_OPERATION_PREVIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW, GtkPrintOperationPreview))>
	endm
GTK_IS_PRINT_OPERATION_PREVIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW))>
	endm
GTK_PRINT_OPERATION_PREVIEW_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW, GtkPrintOperationPreviewIface))>
	endm

GtkPrintOperationPreviewIface STRUC
g_iface			GTypeInterface <>
ready			proc :ptr GtkPrintOperationPreview, :ptr GtkPrintContext
got_page_size		proc :ptr GtkPrintOperationPreview, :ptr GtkPrintContext, :ptr GtkPageSetup
render_page		proc :ptr GtkPrintOperationPreview, :gint
is_selected		proc :ptr GtkPrintOperationPreview, :gint
end_preview		proc :ptr GtkPrintOperationPreview
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkPrintOperationPreviewIface ENDS

;GType
gtk_print_operation_preview_get_type proto __cdecl

;void
gtk_print_operation_preview_render_page proto __cdecl \
	       preview: ptr GtkPrintOperationPreview,
	       page_nr: gint

;void
gtk_print_operation_preview_end_preview proto __cdecl \
	       preview: ptr GtkPrintOperationPreview

;gboolean
gtk_print_operation_preview_is_selected proto __cdecl \
	       preview: ptr GtkPrintOperationPreview,
	       page_nr: gint

G_END_DECLS

endif

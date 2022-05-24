ifndef __GTK_PRINT_OPERATION_PREVIEW_H__
define __GTK_PRINT_OPERATION_PREVIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include cairo.inc
include gtk/gtkprintcontext.inc

define GTK_TYPE_PRINT_OPERATION_PREVIEW <gtk_print_operation_preview_get_type ()>
GTK_PRINT_OPERATION_PREVIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW, GtkPrintOperationPreview))>
  endm
GTK_IS_PRINT_OPERATION_PREVIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW))>
  endm
GTK_PRINT_OPERATION_PREVIEW_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_PRINT_OPERATION_PREVIEW, GtkPrintOperationPreviewIface))>
  endm

;GtkPrintOperationPreview typedef _GtkPrintOperationPreview

_GtkPrintOperationPreviewIface struct
g_iface                 GTypeInterface <>
ready                   proc :ptr, :ptr
got_page_size           proc :ptr, :ptr, :ptr
render_page             proc :ptr, :sdword
is_selected             proc :ptr, :sdword
end_preview             proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
_gtk_reserved6          proc
_gtk_reserved7          proc
_gtk_reserved8          proc
_GtkPrintOperationPreviewIface ends
GtkPrintOperationPreviewIface typedef _GtkPrintOperationPreviewIface

gtk_print_operation_preview_get_type proto
gtk_print_operation_preview_render_page proto :ptr, :sdword
gtk_print_operation_preview_end_preview proto :ptr
gtk_print_operation_preview_is_selected proto :ptr, :sdword

endif

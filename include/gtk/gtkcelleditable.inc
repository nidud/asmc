ifndef __GTK_CELL_EDITABLE_H__
__GTK_CELL_EDITABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_EDITABLE	equ <gtk_cell_editable_get_type>
GTK_CELL_EDITABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_EDITABLE, GtkCellEditable))>
	endm
GTK_CELL_EDITABLE_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_TYPE_CELL_EDITABLE, GtkCellEditableIface))>
	endm
GTK_IS_CELL_EDITABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_EDITABLE))>
	endm
GTK_CELL_EDITABLE_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_CELL_EDITABLE, GtkCellEditableIface))>
	endm

GtkCellEditableIface	STRUC
g_iface			GTypeInterface <>
editing_done		proc :ptr GtkCellEditable
remove_widget		proc :ptr GtkCellEditable
start_editing		proc :ptr GtkCellEditable, :ptr GdkEvent
GtkCellEditableIface	ENDS

;GType
gtk_cell_editable_get_type proto __cdecl

;void
gtk_cell_editable_start_editing proto __cdecl \
	 cell_editable: ptr GtkCellEditable,
		 event: ptr GdkEvent

;void
gtk_cell_editable_editing_done proto __cdecl \
	 cell_editable: ptr GtkCellEditable

;void
gtk_cell_editable_remove_widget proto __cdecl \
	 cell_editable: ptr GtkCellEditable

G_END_DECLS

endif

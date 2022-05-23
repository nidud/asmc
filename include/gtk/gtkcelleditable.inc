ifndef __GTK_CELL_EDITABLE_H__
define __GTK_CELL_EDITABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_CELL_EDITABLE            <gtk_cell_editable_get_type>
GTK_CELL_EDITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_EDITABLE, GtkCellEditable))>
  endm
GTK_IS_CELL_EDITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_EDITABLE))>
  endm
GTK_CELL_EDITABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_CELL_EDITABLE, GtkCellEditableIface))>
  endm

;GtkCellEditable         typedef _GtkCellEditable

_GtkCellEditableIface   struct
g_iface                 GTypeInterface <>
editing_done            proc :ptr
remove_widget           proc :ptr
start_editing           proc :ptr, :ptr
_GtkCellEditableIface   ends
GtkCellEditableIface    typedef _GtkCellEditableIface

gtk_cell_editable_get_type proto
gtk_cell_editable_start_editing proto :ptr, :ptr
gtk_cell_editable_editing_done proto :ptr
gtk_cell_editable_remove_widget proto :ptr

endif
